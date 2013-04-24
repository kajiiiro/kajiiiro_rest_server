#include <stdio.h>
#include <cstring>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string>

#include "define.h"
#include "request.h"
#include "response.h"
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
		FOR(mVecClientSocket) close(*it);
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

	int acceptClient()
	{
		sockaddr_in clientAddress;
		int len = sizeof(clientAddress);
		int client = accept(mSocket, reinterpret_cast<sockaddr *>(&clientAddress)
						, reinterpret_cast<socklen_t *>(&len));
		if (client < 0)
		{
			perror("accept");
			return -1;
		}
		mVecClientSocket.push_back(client);
		return client;
	}

	int mSocket;
	std::vector<int> mVecClientSocket;
	std::string mHost;
	int mPort;
};

bool Session::sendMessage(Response &response) const
{
	std::string strResponse = response.getResponse();
	int result = send(response.getClient(), strResponse.c_str(), strResponse.size(), 0);
	if (result < 0)
		return false;
	return true;
}

bool Session::recvMessage(Request &request) const
{
	P("recv message start");
	char inbuf[1024];
	memset(inbuf, '\0', sizeof(inbuf));
	P("request.getClient");
	int result = recv(request.getClient(), inbuf, sizeof(inbuf), 0);
	if (result < 0)
		return false;
	P("request.setRequest");
	request.setRequest(inbuf);
	return true;
}

Session::Session() : pImpl(new Session::impl())
{

}

Session::~Session()
{
	delete pImpl;
}

bool Session::ready(int iPort)
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
	return true;
}

int Session::startAccept()
{
	return pImpl->acceptClient();
}

bool Session::disconnectSession(const Response &response)
{
	// 保持しているクライアントから除外する
	if (close(response.getClient()) < 0)
	{
		perror("close");
		return false;
	}
	P("disconnect client >> " << response.getClient());
	FOR(pImpl->mVecClientSocket)
	{
		if (response.getClient() == *it)
		{
			pImpl->mVecClientSocket.erase(it);
			break;
		}
	}
	return true;
}

}; // namespace

