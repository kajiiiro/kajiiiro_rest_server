#include "helper.h"
#include "uri.h"

namespace kajiiiro
{

Uri::Uri() : miPort(-1)
{

}

Uri::~Uri()
{

}

bool Uri::setUri(const std::string &strUri)
{
    std::string strTmp = strUri;
    std::string::size_type string_length = FindQueryString(strTmp);
    if (std::string::npos == string_length)
        return false;
    // ?以降は切り取り
    strTmp = strTmp.substr(0, string_length);

    string_length = FindScheme(strTmp);
    if (std::string::npos == string_length)
        return false;
    // ://以降を渡す
    strTmp = strTmp.substr(string_length + 3);

    string_length = FindHost(strTmp);
    if (std::string::npos == string_length)
        return false;
    // /以降を渡す
    strTmp = strTmp.substr(string_length + 1);

    string_length = FindResource(strTmp);
    if (std::string::npos == string_length)
        return false;
    return true;
}

const std::string& Uri::getScheme() const
{
    return mStrScheme;
}

const std::string& Uri::getHost() const
{
    return mStrHost;
}

const std::vector<std::string> &Uri::getResource() const
{
    return mVecStrResource;
}

const std::map<std::string, std::string>& Uri::getQueryString() const
{
    return mQueryString;
}

const int& Uri::getPort() const
{
    return miPort;
}

std::string::size_type Uri::FindScheme(const std::string &strUri)
{
    std::string::size_type location = strUri.find(":");
    if (std::string::npos != location)
        mStrScheme = strUri.substr(0, location);
    return location;
}

// portもここで検出する
std::string::size_type Uri::FindHost(const std::string &strUri)
{
    std::string::size_type location = strUri.find("/");
    std::string strHostPort;
    if (std::string::npos != location)
        strHostPort = strUri.substr(0, location);

    std::string::size_type tmp = strHostPort.find(":");
    if (std::string::npos != tmp)
    {
        mStrHost = strHostPort.substr(0, tmp);
        miPort = atoi(strHostPort.substr(tmp + 1, location - (tmp + 1)).c_str());
    }
    // /の位置を返す
    return location;
}

std::string::size_type Uri::FindResource(const std::string &strUri)
{
    Helper helper;
    std::vector<std::string> vecResource;
    helper.splitStringList(strUri, "/", vecResource);
    return strUri.find_last_of("/");
}

std::string::size_type Uri::FindQueryString(const std::string &strUri)
{
    std::string::size_type location = strUri.find("?");
    std::string strQueryString;
    if (std::string::npos == location)
        return std::string::npos;
    // ?以降を取得
    strQueryString = strUri.substr(location + 1);
    Helper helper;
    std::vector<std::string> vecQueryString;
    helper.splitStringList(strQueryString, "&", vecQueryString);
    std::string::size_type tmp = 0;
    for (auto it = vecQueryString.begin();it != vecQueryString.end();++it)
    {
        tmp = it->find("=");
        if (std::string::npos != tmp)
            mQueryString.insert(std::pair<std::string, std::string>(
                                    it->substr(0, tmp)
                                    , it->substr(tmp + 1)));
    }
    // 返すのは?の位置
    return location;
}

}; // namespace
