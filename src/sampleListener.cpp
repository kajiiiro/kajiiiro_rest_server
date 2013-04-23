#include "define.h"
#include "request.h"
#include "response.h"
#include "session.h"
#include "listener.h"
#include "sampleListener.h"

namespace kajiiiro
{

bool SamplePrintRequestListener::act(const Request &request, Response &response, Session &session)
{
	std::map<std::string, std::string> headerData;
	headerData.insert(std::pair<std::string, std::string>("Content-Type", "text/html"));
	response.setOtherHeader(headerData);
	response.setBody(request.getRequest());
	P("session.sendMessage");
	if (false == session.sendMessage(response))
	{
		E("session.sendMessage");
		return false;
	}
	if (false == session.disconnectSession(response))
	{
		E("session.disconnectSession");
		return false;
	}
	return true;
}

}; // namespace
