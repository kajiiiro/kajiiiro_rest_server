#pragma once

#include "request.h"

namespace kajiiiro
{

class Request::impl
{
public:
	std::string mStrMethod;
	std::string mStrBody;
	std::map<std::string, std::string> mOtherHeader;
	std::vector<std::string> mVecResource;
};

Request::Request() : pImpl(new Request::impl())
{

}

Request::~Request()
{
	delete pImpl;
}

void Request::setRequest(const std::string &strRequest)
{
	std::string newLine("\n");
	std::string std4EasilyWorked = strRequest;
	std::string::size_type sizeNewLine;
	// 改行をすべて\nにする
	while (std::string::npos == (sizeNewLine = std4EasilyWorked.find("\r\n")))
	{
		std4EasilyWorked.replace(sizeNewLine, newLine.size(), newLine);
	}
	// 一行
}

const std::string& Request::getMethod() const
{
	pImpl->mStrMethod;
}

const std::vector<std::string>& Request::getResource() const
{
	pImpl->mVecResource;
}

const std::string& Request::getBody() const
{
	pImpl->mStrBody;
}

const std::map<std::string, std::string>& Request::getOtherHeader() const
{
	pImpl->mOtherHeader;
}

GET / HTTP/1.1
Host: localhost:7766
Connection: keep-alive
Cache-Control: max-age=0
Accept: text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8
User-Agent: Mozilla/5.0 (X11; Linux i686) AppleWebKit/537.22 (KHTML, like Gecko) Ubuntu Chromium/25.0.1364.160 Chrome/25.0.1364.160 Safari/537.22
Accept-Encoding: gzip,deflate,sdch
Accept-Language: ja,en-US;q=0.8,en;q=0.6
Accept-Charset: Shift_JIS,utf-8;q=0.7,*;q=0.3



}; // namespace
