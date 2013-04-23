#include <csignal>
#include <pthread.h>
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
	friend struct ReqResSes4Thread;
	impl() : listener(NULL)
	{
	
	}
	~impl()
	{
		delete listener;
	}
	Listener *listener;
};

// スレッドのためだけの格納構造体
struct ReqResSes4Thread
{
	Request *request;
	Response *response;
	Session *session;
	Listener *listener;
};

void* startThread(void *arg)
{
	ReqResSes4Thread *tmp = static_cast<ReqResSes4Thread*>(arg);
	// 受信
	if (false == tmp->session->recvMessage(*(tmp->request)))
	{
		E("session.recvMessage");
		return arg;
	}
	P("request =============================================== start");
	P(tmp->request->getRequest());
	P("request =============================================== end");
	// 送信
	if (HTTP_METHOD_GET == tmp->request->getMethod())
	{
		tmp->listener->doGet(*(tmp->request), *(tmp->response), *(tmp->session));
	}
	else if (HTTP_METHOD_PUT == tmp->request->getMethod())
	{
		tmp->listener->doPut(*(tmp->request), *(tmp->response), *(tmp->session));
	}
	else if (HTTP_METHOD_POST == tmp->request->getMethod())
	{
		tmp->listener->doPost(*(tmp->request), *(tmp->response), *(tmp->session));
	}
	else if (HTTP_METHOD_DELETE == tmp->request->getMethod())
	{
		tmp->listener->doDelete(*(tmp->request), *(tmp->response), *(tmp->session));
	}
	else
	{
		tmp->response->setStatusCode(405);
		tmp->session->sendMessage(*(tmp->response));
		tmp->session->disconnectSession(*(tmp->response));
	}
	return arg;
}

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
	if (NULL == pImpl->listener)
	{
		E("not set listener");
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
		Request request(iClientFD);
		Response response(iClientFD);
		ReqResSes4Thread threadArg = {&request, &response, &session, pImpl->listener};
		pthread_t threadListener;
		if (0 != pthread_create(&threadListener, NULL, startThread, &threadArg))
		{
			E("pthread_create");
			return false;
		}
		pthread_detach(threadListener);
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
