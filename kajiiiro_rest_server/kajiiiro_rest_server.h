#ifndef KAJIIIRO_REST_SERVER_H
#define KAJIIIRO_REST_SERVER_H

#include <QMainWindow>

namespace Ui {
class kajiiiro_rest_server;
}
class kajiiiro_db;

class kajiiiro_rest_server : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit kajiiiro_rest_server(QWidget *parent = 0);
    ~kajiiiro_rest_server();
    
private slots:
    void on_pushButton_load_clicked();

private:
    Ui::kajiiiro_rest_server *ui;
    kajiiiro_db *m_db;
};

#endif // KAJIIIRO_REST_SERVER_H
