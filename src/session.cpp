#include <stdio.h>
#include <cstring>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string>

#include "session.h"

namespace kajiiiro
{

class Session::impl
{
public:
	impl()
	{
	}
	~impl()
	{
		close(mSocket);
	}

	bool createSocket()
	{
		mSocket = socket(AF_INET, SOCK_STREAM, 0);
		if (mSocket < 0)
		{
			perror("socket");
			return false;
		}
		return true;
	}

	bool readyBindListen()
	{
		int option = 1;
		setsockopt(mSocket, SOL_SOCKET, SO_REUSEADDR, &option, sizeof(option));
		//timeval sendTimeout;
		//sendTimeout.tv_sec = 1;
		//sendTimeout.tv_usec = 0;
		//setsockopt(mSocket, SOL_SOCKET, SO_SNDTIMEO, &send_tv, sizeof(send_tv));
		//timeval recvTimeout;
		//recvTimeout.tv_sec = 1;
		//recvTimeout.tv_usec = 0;
		//setsockopt(mSocket, SOL_SOCKET, SO_RCVTIMEO, &recvTimeout, sizeof(recvTimeout));

		sockaddr_in serverAddress;
		serverAddress.sin_family = AF_INET;
		serverAddress.sin_port = htons(mPort);
		serverAddress.sin_addr.s_addr = INADDR_ANY;
		if (0 != bind(mSocket, reinterpret_cast<sockaddr *>(&serverAddress), sizeof(serverAddress)))
		{
			perror("bind");
			return false;
		}
		if (0 != listen(mSocket, 5))
		{
			perror("listen");
			return false;
		}
		return true;
	}

	bool acceptClient()
	{
		char buf[1024];
		memset(buf, 0, sizeof(buf));
		snprintf(buf, sizeof(buf),
			"HTTP/1.0 200 OK\r\n"
			"Content-Length: 5\r\n"
			"Content-Type: text/html\r\n"
			"\r\n"
			"HELLO\r\n");

		sockaddr_in clientAddress;
		while (1)
		{
			int len = sizeof(clientAddress);
			int sock = accept(mSocket, reinterpret_cast<sockaddr *>(&clientAddress)
							, reinterpret_cast<socklen_t *>(&len));
			if (sock < 0)
			{
				perror("accept");
				break;
			}
			char inbuf[1024];
			memset(inbuf, 0, sizeof(inbuf));
			recv(sock, inbuf, sizeof(inbuf), 0);
			printf("%s", inbuf);
			send(sock, buf, (int)strlen(buf), 0);
			close(sock);
		}
		return true;
	}

	int mSocket;
	std::string mHost;
	int mPort;
};

Session::Session() : pImpl(new Session::impl())
{

}

Session::~Session()
{
	delete pImpl;
}

bool Session::startAccept(int iPort)
{
	pImpl->mPort = iPort;
	if (false == pImpl->createSocket())
	{
		return false;
	}
	if (false == pImpl->readyBindListen())
	{
		return false;
	}
	if (false == pImpl->acceptClient())
	{
		return false;
	}
	return true;
}

}; // namespace

