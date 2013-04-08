#include <QString>
#include <QObject>
#include <QtSql/QSqlQuery>
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

bool kajiiiro_db::connect
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

bool kajiiiro_db::createResource(const QString& uri)
{
    QSqlQuery query("select * from configure");
    while (query.next())
    {
        m_port = query.value(3).toInt();
        ui->label_information->setText(query.value(0).toString()
                                       + query.value(1).toString()
                                       + query.value(2).toString()
                                       + query.value(3).toString()
                                       + query.value(4).toString());
    }
}

bool kajiiiro_db::getConfigure(
        std::map<std::string, std::string>& map_str
        , std::map<std::string, int>& map_int
)
{
    QSqlQuery query("select * from configure");
    while (query.next())
    {
        if (false == query.value(4).toBool())
        {
            // 項目が有効でないなら、処理を飛ばす
            continue;
        }
        if (false == query.value(2).isNull())
        {
            map_str.insert(std::make_pair(query.value(1).toString(), query.value(2).toString()));
        }
        if (false == query.value(3).isNull())
        {
            map_int.insert(std::make_pair(query.value(1).toString(), query.value(3).toInt()));
        }
    }
}
