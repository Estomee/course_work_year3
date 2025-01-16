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

    if (!db.open())
    {

        QTimer::singleShot(5000, [=]()
        {
            createConnection(dbHostName, dbName, userName, dbPassword, dbPort);
        });
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
    dbHostName = "localhost";
    dbName = "postgres";
    userName = "postgres";
    dbPassword = "Lakys2004";
    dbPort = 5432;
}

ConnectionPool::~ConnectionPool()
{
    for (QSqlDatabase& db : availableConnections)
    {
        const QString connectionName = db.connectionName();
        if (db.isOpen())
        {
            db.close();
        }
        db = QSqlDatabase(); //Зануляем объект
        QSqlDatabase::removeDatabase(connectionName);
    }

    for (QSqlDatabase& db : usedConnections)
    {
        const QString connectionName = db.connectionName();
        if (db.isOpen())
        {
            db.close();
        }
        db = QSqlDatabase();
        QSqlDatabase::removeDatabase(connectionName);
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

QSqlQuery ConnectionPool::executeQuery(const QString& query, const QVariantMap& parameters) //Выполнение запроса
{
    QSqlDatabase connection = getConnection();
    if (!connection.isOpen()) {
        qDebug() << "Database connection is not open";
    }

    QSqlQuery result(connection);

        result.prepare(query);
        for (auto it = parameters.constBegin(); it != parameters.constEnd(); ++it)
        {
            result.bindValue(it.key(), it.value());
        }
        result.exec();

    releaseConnection(connection);
    return result;
}

void ConnectionPool::executeQueryAsync(const QString& query, QObject* receiver, const char* slot, const QVariantMap& parameters) //Бизнесс-логика выполнения запросов в многопоточном режиме
{
    QueryTask* task = new QueryTask(this, query, parameters);
    QObject::connect(task, SIGNAL(queryCompleted(QSqlQuery)), receiver, slot); //Объект получения - receiver, slot - фукнция, которая будет вызвана при испускании сигнала
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

