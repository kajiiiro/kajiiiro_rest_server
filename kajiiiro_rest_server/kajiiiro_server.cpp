#include <QtNetwork/QTcpServer>
#include <QtNetwork/QTcpSocket>
#include <QtGui/QMessageBox>
#include "kajiiiro_server.h"

kajiiiro_server::kajiiiro_server() :
    m_server(new QTcpServer(0))
{
}

bool kajiiiro_server::session(const int port, QString &error_msg)
{
    if (false == m_server->listen(QHostAddress::Any, port))
    {
        error_msg = m_server->errorString();
        return false;
    }
    return true;
}

bool kajiiiro_server::send()
{
    sleep(5);
    QTcpSocket *client = m_server->nextPendingConnection();
    QStringList lines;
    while (client->canReadLine())
        lines.append(client->readLine());
    QMessageBox::information(
                0
                ,QObject::tr("receive\n")
                ,lines.join("/")
                ,QMessageBox::Ok);
    QDataStream out(client);
    // disconnect
    out << quint16(0xFFFF);
    client->close();
    return true;
}

QTcpServer* kajiiiro_server::getServer()
{
    return m_server;
}
