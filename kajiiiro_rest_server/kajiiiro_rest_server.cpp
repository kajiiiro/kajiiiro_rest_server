#include <QtSql/QSqlQuery>
#include "kajiiiro_rest_server.h"
#include "ui_kajiiiro_rest_server.h"
#include "kajiiiro_db.h"

kajiiiro_rest_server::kajiiiro_rest_server(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::kajiiiro_rest_server),
    m_db(new kajiiiro_db())
{
    ui->setupUi(this);
}

kajiiiro_rest_server::~kajiiiro_rest_server()
{
    delete ui;
    delete m_db;
}

void kajiiiro_rest_server::on_pushButton_load_clicked()
{
    if (false == m_db->connectDB(
                ui->lineEdit_host->text()
                ,ui->lineEdit_db_name->text()
                ,ui->lineEdit_user->text()
                ,ui->lineEdit_pass->text()
                ))
    {
        return;
    }
    QSqlQuery query("select * from configure");
    while (query.next())
    {
        ui->label_information->setText(query.value(0).toString()
                                       + query.value(1).toString()
                                       + query.value(2).toString()
                                       + query.value(3).toString()
                                       + query.value(4).toString());
    }
}
