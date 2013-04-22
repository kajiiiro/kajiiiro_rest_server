#include "define.h"
#include "db.h"
#include "request.h"
#include "response.h"
#include "session.h"
#include "server.h"

namespace kajiiiro
{

class Server::impl
{
public:
	int id;
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
	if (false == session.ready(iPort))
		return false;

	int iClientFD = session.startAccept();
	if (iClientFD < 0)
		return false;
	// 受信
	Request request(iClientFD);
	session.recvMessage(request);
	P("=====  recv [" << request.getRequest() <<  "]");
	// 送信
	Response response(iClientFD);
	std::map<std::string, std::string> headerData;
	headerData.insert(std::pair<std::string, std::string>(
		"Content-Type", "text/html"));
	response.setOtherHeader(headerData);
	response.setBody("<h1>Hello<h1>");
	session.sendMessage(response);
	return true;
}

}; // namespace
