#include <QtSql/QSqlQuery>
#include <QtNetwork/QTcpServer>
#include "kajiiiro_db.h"
#include "kajiiiro_server.h"
#include "kajiiiro_rest_server.h"
#include "ui_kajiiiro_rest_server.h"

kajiiiro_rest_server::kajiiiro_rest_server(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::kajiiiro_rest_server),
    m_db(new kajiiiro_db()),
    m_server(NULL),
    m_port(7766)
{
    ui->setupUi(this);
}

kajiiiro_rest_server::~kajiiiro_rest_server()
{
    delete ui;
    ui = NULL;
    delete m_db;
    m_db = NULL;
    delete m_server;
    m_server = NULL;
}

void kajiiiro_rest_server::on_pushButton_load_clicked()
{
    if (false == m_db->connect(
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
        m_port = query.value(3).toInt();
        ui->label_information->setText(query.value(0).toString()
                                       + query.value(1).toString()
                                       + query.value(2).toString()
                                       + query.value(3).toString()
                                       + query.value(4).toString());
    }
}

void kajiiiro_rest_server::on_pushButton_start_clicked()
{
    if (NULL != m_server)
    {
        ui->label_status->setText("already running");
        return;
    }
    // サーバ起動
    m_server = new kajiiiro_server;
    std::string str_msg;
    m_server->start(str_msg);
    ui->textBrowser->setText(str_msg.c_str());
    ui->label_status->setText("running server");
}

void kajiiiro_rest_server::on_pushButton_stop_clicked()
{
    if (NULL == m_server)
    {
        ui->label_status->setText("not running yet");
        return;
    }
    // サーバ停止
    delete m_server;
    m_server = NULL;
    ui->label_status->setText("stop server");
}
