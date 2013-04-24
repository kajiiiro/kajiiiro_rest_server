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

// スレッドのためだけのポインタ格納構造体
struct ReqResSes4Thread
{
	Request *request;
	Response *response;
	Session *session;
	Listener *listener;
};

// NULLを代入しているので、何度関数を呼んでも安心！
// というかdeleteがNULL代入もやってくれよ……
void deletePointerAndSetNull(ReqResSes4Thread *pointerBox)
{
	delete pointerBox->request;
	pointerBox->request = NULL;
	delete pointerBox->response;
	pointerBox->response = NULL;
}

// request, responseはメモリを解放する必要がある
void* startThread(void *arg)
{
	Request *request = (static_cast<ReqResSes4Thread*>(arg))->request;
	Response *response = (static_cast<ReqResSes4Thread*>(arg))->response;
	Session *session = (static_cast<ReqResSes4Thread*>(arg))->session;
	Listener *listener = (static_cast<ReqResSes4Thread*>(arg))->listener;
	// 受信
	P("recv request");
	do
	{
		if (false == session->recvMessage(*request))
		{
			E("session.recvMessage");
			break;
		}
		P("request =============================================== start");
		P(request->getRequest());
		P("request =============================================== end");
		// 送信
		P("check method");
		if (HTTP_METHOD_GET == request->getMethod())
		{
			P("do get");
			listener->doGet(*request, *response, *session);
		}
		else if (HTTP_METHOD_PUT == request->getMethod())
		{
			P("do put");
			listener->doPut(*request, *response, *session);
		}
		else if (HTTP_METHOD_POST == request->getMethod())
		{
			P("do post");
			listener->doPost(*request, *response, *session);
		}
		else if (HTTP_METHOD_DELETE == request->getMethod())
		{
			P("do delete");
			listener->doDelete(*request, *response, *session);
		}
		else
		{
			E("not supported method");
			response->setStatusCode(405);
			session->sendMessage(*response);
			session->disconnectSession(*response);
		}
	}
	while (false);
	deletePointerAndSetNull(static_cast<ReqResSes4Thread*>(arg));
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
	pthread_t threadListener;
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
		Request *request = new Request(iClientFD);
		Response *response = new Response(iClientFD);
		ReqResSes4Thread threadArg = {request, response, &session, pImpl->listener};
		// request, responseはスレッドの関数内部でメモリを解放する必要がある
		P("thread start");
		if (0 != pthread_create(&threadListener, NULL, startThread, &threadArg))
		{
			E("pthread_create");
			// スレッドの作成に失敗した場合は自分でエラー処理でメモリを解放する
			deletePointerAndSetNull(&threadArg);
			return false;
		}
		P("thread end");
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
