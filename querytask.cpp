#include "querytask.h"
#include "database.h"

QueryTask::QueryTask(ConnectionPool* pool, const QString& query)
    : m_pool(pool), m_query(query)
{
    setAutoDelete(true);
}

void QueryTask::run()
{
    QSqlQuery result = m_pool->executeQuery(m_query);
    emit queryCompleted(result);
}
