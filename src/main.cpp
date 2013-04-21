#include <iostream>

#include "helper.h"
#include "db.h"
#include "uri.h"
#include "session.h"

#define P(message) std::cout << message << std::endl
#define E(message) std::cerr << message << std::endl
#define FOR(stl) for (auto it = stl.begin();it != stl.end();++it)

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

void testDb()
{
	kajiiiro::Db config;
    const string SERVER_PORT = "port";
    config.addValue(SERVER_PORT, 80);
    int iPort = 0;
    if (false == config.getValue(SERVER_PORT, iPort))
    {
        E("get " << SERVER_PORT << " error");
        return;
    }
    P(SERVER_PORT << " = " << iPort);
}

void testSession()
{
	P("start");
	kajiiiro::Session session;
	if (false == session.startAccept(7766))
	{
		E("accept error");
		return;
	}
	P("accept ok");
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
		FOR(vec_str) P("[" << *it << "]");
	}
}

int main(int argc, char **argv)
{
//    testSession();
	testHelper();
    return 0;
}


