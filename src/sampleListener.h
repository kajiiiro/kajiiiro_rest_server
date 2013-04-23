#pragma once

namespace kajiiiro
{

class Session;
class Request;
class Response;
class Listener;

// リソースごとに紐付けられた文字列を返すサンプル
class SampleRestListener : public Listener
{
public:
	SampleRestListener();
	~SampleRestListener();
	void doGet(const Request &request, Response &response, Session &session);
	void doPut(const Request &request, Response &response, Session &session);
	void doPost(const Request &request, Response &response, Session &session);
	void doDelete(const Request &request, Response &response, Session &session);

private:
	class impl;
	impl *pImpl;
};

}; // namespace
