#include "define.h"
#include "helper.h"
#include "uri.h"
#include "session.h"
#include "request.h"
#include "response.h"
#include "server.h"
#include "listener.h"
#include "sampleListener.h"

using namespace std;

void testUri()
{
	kajiiiro::Uri uri;
	string strUri = "http://localhost:8080/kajiro/yota/?age=24&action=delete";
	if (false == uri.setUri(strUri))
	{
		E("set uri [" << strUri << "] error");
		return;
	}
	P("scheme  : " << uri.getScheme());
	P("host    : " << uri.getHost());
	P("port    : " << uri.getPort());
	FOR(uri.getResource()) P("resource: " << *it);
	FOR(uri.getQueryString()) P(it->first << ", " << it->second);
}

void testHelper()
{
	kajiiiro::Helper helper;
	std::string str = "  trim test word       ";
	P("[" << str << "]");
	str = helper.trimWhiteSpace(str);
	P("[" << str << "]");
	str = "   split  test   word   ";
	std::vector<std::string> vec_str;
	P("[" << str << "]");
	if (helper.splitStringList(str, " ", vec_str))
	{
		FOR_P(vec_str);
	}
	str = helper.getAfterKeyWord(helper.trimWhiteSpace(str), "t");
	P("[" << str << "]");
	str = helper.getBeforeKeyWord(str, "w");
	P("[" << str << "]");
	if (helper.getAfterKeyWord(str, "a").empty())
		P("empty");
	str = helper.getAfterKeyWord(str, "   ");
	P("[" << str << "]");
}

void testRequest()
{
	std::string str = "GET / HTTP/1.1\r\n"
"Host: localhost:7766\r\n"
"Connection: keep-alive\r\n"
"Cache-Control: max-age=0\r\n"
"Accept: text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8\r\n"
"User-Agent: Mozilla/5.0 (X11; Linux i686) AppleWebKit/537.22 (KHTML, like Gecko) Ubuntu Chromium/25.0.1364.160 Chrome/25.0.1364.160 Safari/537.22\r\n"
"Accept-Encoding: gzip,deflate,sdch\r\n"
"Accept-Language: ja,en-US;q=0.8,en;q=0.6\r\n"
"Accept-Charset: Shift_JIS,utf-8;q=0.7,*;q=0.3\r\n\r\n";
	kajiiiro::Request request(1);
	request.setRequest(str);
	P("[" << request.getMethod() << "]");
	P("[" << request.getBody() << "]");
	FOR_P(request.getResource());
	FOR(request.getOtherHeader())
	{
		P("[" << it->first << " : " << it->second << "]");
	}
}

void testResponse()
{
//	HTTP/1.1 200 OK
//Date: Mon, 22 Apr 2013 02:59:54 GMT
//Server: Apache/2.2.14
//X-Powered-By: PHP/5.3.2-1ubuntu4.19
//X-Pingback: http://99blues.dyndns.org/blog/xmlrpc.php
//Vary: Accept-Encoding
//Keep-Alive: timeout=15, max=100
//Content-Type: text/html; charset=UTF-8
//Via: 1.1 ws0.isb.co.jp
//X-NAI-ID: 7796_e18e_5f48c272_aaf8_11e2_8501_001d0963a47e
//Connection: Close

//HTTP/1.0 200 OK
//X-Content-Type-Options: nosniff
//Content-Language: ja
//Last-Modified: Wed, 03 Apr 2013 04:04:19 GMT
//Content-Length: 50899
//Content-Type: text/html; charset=UTF-8
//Date: Mon, 22 Apr 2013 01:38:27 GMT
//Server: Apache
//Cache-Control: private, s-maxage=0, max-age=0, must-revalidate
//Vary: Accept-Encoding,Cookie
//Age: 5913
//X-Cache: HIT from cp1009.eqiad.wmnet
//X-Cache-Lookup: HIT from cp1009.eqiad.wmnet:3128
//X-Cache: MISS from cp1001.eqiad.wmnet
//X-Cache-Lookup: MISS from cp1001.eqiad.wmnet:80
//Connection: keep-alive
//Via: 1.1 ws0.isb.co.jp
//X-NAI-ID: 779a_4904_189a016c_aafb_11e2_80cc_001d0963a47e
	std::map<std::string, std::string> headerData;
	headerData.insert(std::pair<std::string, std::string>(
		"Content-Type", "text/html"));
	kajiiiro::Response response(1);
	response.setOtherHeader(headerData);
	response.setBody("<h1>Hello<h1>");
	P("[" << response.getResponse() << "]");
}

void testServer()
{
	kajiiiro::Server server;
	P("start");
	server.setListener(new kajiiiro::SampleRestListener());
	server.start();
	P("stop");
}

int main(int argc, char **argv)
{
//	testSession();
//	testHelper();
//	testRequest();
//	testResponse();
	testServer();
	return 0;
}


