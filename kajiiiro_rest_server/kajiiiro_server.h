#ifndef KAJIIIRO_SERVER_H
#define KAJIIIRO_SERVER_H

class QString;
class QTcpServer;

class kajiiiro_server
{
public:
    kajiiiro_server();
    bool session(int port, QString& error_msg);
    bool send();
    QTcpServer* getServer();

private:
    QTcpServer *m_server;
};

#endif // KAJIIIRO_SERVER_H
