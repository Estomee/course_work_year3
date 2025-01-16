#ifndef QUERYTASK_H
#define QUERYTASK_H

#include <QObject>
#include <QRunnable>
#include <QtSql/QSqlQuery>

class ConnectionPool;

class QueryTask : public QObject, public QRunnable
{
    Q_OBJECT
public:
    QueryTask(ConnectionPool* pool, const QString& query, const QVariantMap& parameters);

signals:
    void queryCompleted(QSqlQuery result);

private:
    ConnectionPool* m_pool;
    QString m_query;
    const QVariantMap& m_parameters;
    void run() override;
};

#endif // QUERYTASK_H
