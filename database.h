#ifndef DATABASE_H
#define DATABASE_H
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QMutex>
#include <QWaitCondition>
#include <QRunnable>
#include <QThreadPool>
#include <QObject>
#include <QThread>
#include <QMutex>
#include <QFuture>
#include "QMessageBox"
#include <QFuture>
#include <QPromise>
#include <QFuture>
#include <QtConcurrent/QtConcurrent>
#include "qapplication.h"
#include "querytask.h"



//Реализация подключеняи к базе данных через фабричный метод

class DatabaseInterfaceConnection //Интерфейс для класса подключения
{
    public:
        virtual QSqlDatabase createConnection(const QString& dbHostName,
                                          const QString& dbName,
                                          const QString& userName,
                                          const QString& dbPasword ,
                                          const int& dbPort) =0;
        virtual ~DatabaseInterfaceConnection() = default;
};

class ConnectionPool //ConnectionPool для работы с подключениями
{
    private:
        void preformQuerry();
        virtual DatabaseInterfaceConnection* FactoryConnection() = 0;
        void someLogics();
        QSqlDatabase getConnection();
        void releaseConnection(QSqlDatabase connection);
        static QVector<QSqlDatabase> availableConnections;
        static QVector<QSqlDatabase> usedConnections;
        static QMutex mutex;
        static QWaitCondition connectionAvailable;

        QString dbHostName;
        QString dbName;
        QString userName;
        QString dbPassword;
        int dbPort;



    public:
        QSqlQuery executeQuery(const QString& query);
        void executeQueryAsync(const QString& query, QObject* receiver, const char* slot);
        void initializePool();
        virtual ~ConnectionPool();
        ConnectionPool();
};

class ConcreteDbCConnection: public ConnectionPool //DatabaseConnection Creator
{
    private:
        DatabaseInterfaceConnection* FactoryConnection() override;
};

class DatabaseConnection: public DatabaseInterfaceConnection
{
    private:
        QSqlDatabase db;

    protected:
        QSqlDatabase createConnection(const QString& dbHostName,
                                  const QString& dbName,
                                  const QString& userName,
                                  const QString& dbPassword,
                                  const int& dbPort) override;

};

#endif // DATABASE_H
