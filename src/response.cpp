#include "define.h"
#include "helper.h"
#include "response.h"
#include <sstream>

namespace kajiiiro
{

class Response::impl
{
public:
	int mClientFD;
	int mStatusCode;
	std::map<std::string, std::string> mOtherHeader;
	bool mIsTransforEncoding;
	std::string mBody;
	std::string mContentLength;
	impl(const int &iClientFD) :mClientFD(iClientFD)
		, mStatusCode(200), mIsTransforEncoding(false)
	{
	
	}
	std::string getStatusCodeWord() const
	{
		switch (mStatusCode)
		{
			break; case 200: return STATUSCODEWORD_200;
			break; case 201: return STATUSCODEWORD_201;
			break; case 204: return STATUSCODEWORD_204;
			break; case 303: return STATUSCODEWORD_303;
			break; case 400: return STATUSCODEWORD_400;
			break; case 403: return STATUSCODEWORD_403;
			break; case 404: return STATUSCODEWORD_404;
			break; case 405: return STATUSCODEWORD_405;
			break; case 500: return STATUSCODEWORD_500;
			break; default: return std::string();
		}
	}
};

Response::Response(const int &iClientFD) : pImpl(new Response::impl(iClientFD))
{

}

Response::~Response()
{
	delete pImpl;
}

std::string Response::getResponse() const
{
	std::string strResponse;
	strResponse += HTTP_VERSION + WHITESPACE + pImpl->getStatusCodeWord() + LINE_DELIMITER;
	if (pImpl->mIsTransforEncoding)
		strResponse += HTTP_HEADER_TRANSFOR_ENCODING;
	else
		strResponse += pImpl->mContentLength;
	FOR(pImpl->mOtherHeader)
	{
		strResponse += it->first + HTTP_HEADER_DELIMITER + WHITESPACE + it->second + LINE_DELIMITER;
	}
	strResponse += HTTP_BODY_DELIMITER;
	strResponse += pImpl->mBody;
	return strResponse;
}

int Response::getClient() const
{
	return pImpl->mClientFD;
}

void Response::setStatusCode(const int &iStatusCode)
{
	pImpl->mStatusCode = iStatusCode;
}

void Response::setOtherHeader(const std::map<std::string, std::string> &OtherHeader)
{
	pImpl->mOtherHeader = OtherHeader;
}

bool Response::setBody(const std::string &strBody)
{
	if (pImpl->mIsTransforEncoding)
		return false;
	pImpl->mBody = strBody;
	std::stringstream ss;
	ss << HTTP_HEADER_CONTENT_LENGTH << HTTP_HEADER_DELIMITER << WHITESPACE << pImpl->mBody.size() << LINE_DELIMITER;
	pImpl->mContentLength = ss.str();
	return true;
}

bool Response::appendBody(const std::string &strBody)
{
	// 本当はsenderを保持してここで送信する必要がある？？
	if (false == pImpl->mIsTransforEncoding)
		return false;
	std::stringstream ss;
	ss << strBody.size() << LINE_DELIMITER << strBody;
	pImpl->mBody = ss.str();
	return true;
}

void Response::setTransforEncoding(const bool &bChunked)
{
	pImpl->mIsTransforEncoding = bChunked;
}

}; // namespace
