#include <QString>
#include <QObject>
#include <QtSql/QSqlError>
#include <QtSql/QSqlDatabase>
#include <QtSql/QPSQLDriver>
#include <QtGui/QMessageBox>
#include "kajiiiro_db.h"

kajiiiro_db::kajiiiro_db()
{
    // ここではメモリを確保せず、
    // 接続時のフラグとしてNULLで初期化する
    m_db = NULL;
}

kajiiiro_db::~kajiiiro_db()
{
    delete m_db;
}

bool kajiiiro_db::connectDB
(
    const QString &host
    ,const QString &db_name
    ,const QString &user
    ,const QString &pass
)
{
    if (NULL != m_db)
    {
        // already connect
        return true;
    }
    m_db = new QSqlDatabase();
    *m_db = QSqlDatabase::addDatabase("QPSQL");
    m_db->setHostName(host);
    m_db->setDatabaseName(db_name);
    m_db->setUserName(user);
    m_db->setPassword(pass);
    if (false == m_db->open())
    {
        QMessageBox::critical(
                    0
                    ,QObject::tr("databese error")
                    ,m_db->lastError().text()
                    ,QMessageBox::Cancel);
        return false;
    }
    return true;
}
