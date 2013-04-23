#include <csignal>
#include "define.h"
#include "request.h"
#include "response.h"
#include "session.h"
#include "server.h"
#include "listener.h"

namespace kajiiiro
{

void catchSignal(int sig)
{
	P("");
	P("BYE");
	P("");
	exit(0);
}

class Server::impl
{
public:
	impl() : listener(NULL)
	{
	
	}
	~impl()
	{
		delete listener;
	}
	Listener *listener;
	void callListener(const Request &request, Response &response, Session &session)
	{
		if (NULL == listener)
		{
			E("not set listener");
			return;
		}
		if (HTTP_METHOD_GET == request.getMethod())
		{
			listener->doGet(request, response, session);
		}
		else if (HTTP_METHOD_PUT == request.getMethod())
		{
			listener->doPut(request, response, session);
		}
		else if (HTTP_METHOD_POST == request.getMethod())
		{
			listener->doPost(request, response, session);
		}
		else if (HTTP_METHOD_DELETE == request.getMethod())
		{
			listener->doDelete(request, response, session);
		}
		else
		{
			response.setStatusCode(405);
			session.sendMessage(response);
		}
	}
};

Server::Server() : pImpl(new impl())
{

}

Server::~Server()
{
	delete pImpl;
}

bool Server::start(int iPort)
{
	Session session;
	P("session.ready");
	if (false == session.ready(iPort))
	{
		E("session.ready");
		return false;
	}

	signal(SIGINT, catchSignal);
	while (1)
	{
		P("session.startAccept");
		int iClientFD = session.startAccept();
		if (iClientFD < 0)
		{
			E("session.startAccept");
			return false;
		}
		P("client >> " << iClientFD);
		// 受信
		Request request(iClientFD);
		P("session.recvMessage");
		if (false == session.recvMessage(request))
		{
			E("session.recvMessage");
			return false;
		}
		// 送信
		Response response(iClientFD);
		pImpl->callListener(request, response, session);
	}
	return true;
}

bool Server::setListener(Listener *listener)
{
	if (NULL != pImpl->listener)
	{
		E("pImpl->listener");
		return false;
	}
	// listenerの登録
	pImpl->listener = listener;
	return true;
}

}; // namespace
