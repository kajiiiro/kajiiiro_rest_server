#pragma once

namespace kajiiiro
{

class Request;
class Response;

// Uriを扱うクラス
class Session
{
public:
	Session();
	~Session();
	Session(const Session &copy) = delete;
	const Session& operator=(const Session &copy) = delete;
	bool ready(int iPort);
	int startAccept();
	bool sendMessage(Response &response);
	bool recvMessage(Request &request);

private:
	class impl;
	impl *pImpl;
};


}; // namespace
