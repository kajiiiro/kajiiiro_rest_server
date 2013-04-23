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
	virtual bool act(const Request &request, Response &response, Session &session) = 0;
};

}; // namespace
