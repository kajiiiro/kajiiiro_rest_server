#ifndef KAJIIIRO_DB_H
#define KAJIIIRO_DB_H

class QSqlDatabase;
class QString;

class kajiiiro_db
{
public:
    kajiiiro_db();
    ~kajiiiro_db();
    bool connect
    (
        const QString& host
        ,const QString& db_name
        ,const QString& user
        ,const QString& pass
    );
private:
    QSqlDatabase *m_db;
};

#endif // KAJIIIRO_DB_H
