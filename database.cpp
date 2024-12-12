#include "database.h"

QVector<QSqlDatabase> ConnectionPool::availableConnections;
QVector<QSqlDatabase>  ConnectionPool::usedConnections;
QWaitCondition ConnectionPool::connectionAvailable;
QMutex ConnectionPool::mutex;

QSqlDatabase DatabaseConnection::createConnection(
                                       const QString& dbHostName,
                                       const QString& dbName,
                                       const QString& userName,
                                       const QString& dbPassword,
                                       const int& dbPort)
{

    static int connectionCounter = 0;
    QString connectionName = QString("Connection_%1").arg(++connectionCounter);

    QSqlDatabase db = QSqlDatabase::addDatabase("QPSQL", connectionName);

    db.setHostName(dbHostName);
    db.setDatabaseName(dbName);
    db.setUserName(userName);
    db.setPassword(dbPassword);
    db.setPort(dbPort);

    if (!db.open()) //Нужно доделать момент, когда не получается подключиться к серверу (на 09.12.24 программа просто завершает свою работу аварийно
    {
        QMessageBox::critical(nullptr, "Ошибка", "Тут текст");
        QCoreApplication::quit();
    }
    else
    {
        return db;
    }
}


DatabaseInterfaceConnection* ConcreteDbCConnection::FactoryConnection() //Возвращает объект подключения
{
    return new DatabaseConnection();
}

ConnectionPool::ConnectionPool()
{
    dbHostName = "172.20.7.54";
    dbName = "db2091_20";
    userName = "st2091";
    dbPassword = "pwd_2091";
    dbPort = 5432;
}

ConnectionPool::~ConnectionPool()
{
    for (QSqlDatabase& db : availableConnections)
    {
        if (db.isOpen())
        {
            db.close();
        }
        QSqlDatabase::removeDatabase(db.connectionName());
    }

    for (QSqlDatabase& db : usedConnections)
    {
        if (db.isOpen())
        {
            db.close();
        }
        QSqlDatabase::removeDatabase(db.connectionName());
    }
}

QSqlDatabase ConnectionPool::getConnection()
{
    QMutexLocker locker(&mutex); // Автоматически освобождает мьютекс при выходе из области видимости

    while (availableConnections.isEmpty())
    {
        // Ждем, пока появится свободное подключение
        connectionAvailable.wait(&mutex);
    }

    QSqlDatabase connection = availableConnections.takeFirst();
    usedConnections.append(connection);
    return connection;
}

void ConnectionPool::releaseConnection(QSqlDatabase connection) //Освобождаем подключение
{
    QMutexLocker locker(&mutex);

    QString connectionName = connection.connectionName();
    for (int i = 0; i < usedConnections.size(); ++i)
    {
        if(usedConnections[i].connectionName() == connectionName)
        {
            usedConnections.removeAt(i);
            break;
        }
    }
    availableConnections.append(connection);

    // Уведомляем ожидающие потоки о появлении свободного подключения
    connectionAvailable.wakeOne();
}

QSqlQuery ConnectionPool::executeQuery(const QString& query) //Выполнение запроса
{
    QSqlDatabase connection = getConnection();
    QSqlQuery result(connection);

    result.exec(query);

    releaseConnection(connection);
    return result;
}

void ConnectionPool::executeQueryAsync(const QString& query, QObject* receiver, const char* slot) //Бизнесс-логика выполнения запросов в многопоточном режиме
{
    QueryTask* task = new QueryTask(this, query);
    QObject::connect(task, SIGNAL(queryCompleted(QSqlQuery)), receiver, slot);
    QThreadPool* threadPool = QThreadPool::globalInstance();
    int threadCount = QThread::idealThreadCount();
    threadPool->setMaxThreadCount(threadCount);
    threadPool->start(task);
}

void ConnectionPool::initializePool() //Инициализация пула соединений
{
    QList<QFuture<void>> futures;
    const int numConnections = 5;

    for (int i = 0; i < numConnections; i++)
    {
        futures.append(QtConcurrent::run([this, i]() {
            DatabaseInterfaceConnection* connection = this->FactoryConnection();
            QString connectionName = QString("connection_%1").arg(i + 1);
            
            QMutexLocker locker(&mutex); // Защищаем создание соединения
            QSqlDatabase newDb = QSqlDatabase::addDatabase("QPSQL", connectionName);
            locker.unlock(); // Разблокируем мьютекс после создания соединения
            
            newDb = connection->createConnection(dbHostName, dbName, userName, dbPassword, dbPort);
            newDb.setConnectOptions("connect_timeout=5"); // Добавляем таймаут

            if (newDb.isOpen())
            {
                QMutexLocker locker(&mutex); // Защищаем добавление в вектор
                availableConnections.append(newDb);
            }

            delete connection;
        }));
    }

    // Ждем завершения всех подключений
    for (auto& future : futures)
    {
        future.waitForFinished();
    }
}

void ConnectionPool::someLogics() //Проверить нужно ли мне в отдельном треде делать инициализацию
{
    // Создаем поток для инициализации пула подключений
    QThread* initThread = QThread::create([this]()
    {
        initializePool();
    });

    // Запускаем поток
    initThread->start();

    // Ждем завершения инициализации
    initThread->wait();
    delete initThread;
}
