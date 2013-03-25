#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <cstring>
#include "kajiiiro_server.h"

int kajiiiro_server::start(std::string &str_msg)
{
    int i_server;
    int i_client;
    int i_port = 7766;
    {
        i_server = socket(AF_INET, SOCK_STREAM, 0);
        if (i_server < 0)
        {
            return SERVER_ERROR;
        }
        sockaddr_in reader_addr;
        memset(&reader_addr, '\0', sizeof(reader_addr));
        reader_addr.sin_family = AF_INET;
        reader_addr.sin_addr.s_addr = htonl(INADDR_ANY);
        reader_addr.sin_port = htons(i_port);
        if (bind(i_server, reinterpret_cast<sockaddr*>(&reader_addr), sizeof(reader_addr)) < 0)
        {
            close(i_server);
            return SERVER_ERROR;
        }
        if (listen(i_server, 1) < 0)
        {
            close(i_server);
            return SERVER_ERROR;
        }
        sockaddr_in writer_addr;
        memset(&writer_addr, '\0', sizeof(writer_addr));
        socklen_t socket_len;
        i_client = accept(i_server,reinterpret_cast<sockaddr*>(&writer_addr), &socket_len);
        if (i_client < 0)
        {
            close(i_server);
            return SERVER_ERROR;
        }
        char c_buf[1024];
        memset(c_buf, '\0', 1024);
        if (read(i_client, c_buf, 1024) <= 0)
        {
            close(i_server);
            close(i_client);
            return SERVER_ERROR;
        }
        str_msg = c_buf;
        char c_send[] = "HTTP/1.0 200 OK\r\nContent-Length: 13\r\nContent-Type: text/html\r\n\r\nhello, world.";
        if (send(i_client, c_send, sizeof(c_send), 0) < 0)
        {
            close(i_server);
            close(i_client);
            return SERVER_ERROR;
        }
    }
    close(i_server);
    close(i_client);
    return SERVER_SUCCESS;
}

