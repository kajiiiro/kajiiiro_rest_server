#include <csignal>
#include "define.h"
#include "db.h"
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
};

Server::Server() : pImpl(new impl())
{

}

Server::~Server()
{
	delete pImpl;
}

bool Server::start(const Db &config)
{
	int iPort = 0;
	// 設定がなければデフォルトを使用
	if (false == config.getValue(SERVER_PORT, iPort))
		iPort = 7766;

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
		if (false == pImpl->listener->act(request, response, session))
		{
			E("listener.act");
			return false;
		}
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
