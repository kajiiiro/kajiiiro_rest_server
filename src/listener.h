#pragma once

namespace kajiiiro
{

class Request;
class Response;
class Session;

class Listener
{
public:
	// リスナーに送信を行うクラスSessionを渡す
	// そうしないと、トランスファーエンコーディングが面倒になるし、
	// なによりも、クライアントとの切断タイミングがこちらではわからない
	virtual void doGet(const Request &request, Response &response, Session &session) = 0;
	virtual void doPut(const Request &request, Response &response, Session &session) = 0;
	virtual void doPost(const Request &request, Response &response, Session &session) = 0;
	virtual void doDelete(const Request &request, Response &response, Session &session) = 0;
};

}; // namespace
