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
	bool sendMessage(Response &response) const;
	bool recvMessage(Request &request) const;
	bool disconnectSession(const Response &response);

private:
	class impl;
	impl *pImpl;
};


}; // namespace
