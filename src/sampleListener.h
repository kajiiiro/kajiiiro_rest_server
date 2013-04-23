#pragma once

namespace kajiiiro
{

class Session;
class Request;
class Response;
class Listener;

class SamplePrintRequestListener : public Listener
{
public:
	bool act(const Request &request, Response &response, Session &session);
};

}; // namespace
