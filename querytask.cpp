#include "querytask.h"
#include "database.h"

QueryTask::QueryTask(ConnectionPool* pool, const QString& query, const QVariantMap& parameters)
    : m_pool(pool), m_query(query), m_parameters(parameters)
{
    setAutoDelete(true);
}

void QueryTask::run()
{
    QSqlQuery result = m_pool->executeQuery(m_query, m_parameters);
    emit queryCompleted(result);
}
