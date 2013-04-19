#include <iostream>

#include "db.h"
#include "uri.h"

#define P(message) std::cout << message << std::endl
#define E(message) std::cerr << message << std::endl
#define FOR(stl) for (auto it = stl.begin();it != stl.end();++it)

using namespace std;

int main(int argc, char **argv)
{
    kajiiiro::Db config;
    const string SERVER_PORT = "port";
    config.addValue(SERVER_PORT, 80);
    int iPort = 0;
    if (false == config.getValue(SERVER_PORT, iPort))
    {
        E("get " << SERVER_PORT << " error");
        return 1;
    }
    P(SERVER_PORT << " = " << iPort);
    kajiiiro::Uri uri;
    string strUri = "http://localhost:8080/kajiro/yota/?age=24&action=delete";
    if (false == uri.setUri(strUri))
    {
        E("set uri [" << strUri << "] error");
        return 1;
    }
    P("scheme  : " << uri.getScheme());
    P("host    : " << uri.getHost());
    P("port    : " << uri.getPort());
    FOR(uri.getResource()) P("resource: " << *it);
    FOR(uri.getQueryString()) P(it->first << ", " << it->second);
    return 0;
}


