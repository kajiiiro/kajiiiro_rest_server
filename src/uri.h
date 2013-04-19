#pragma once

#include <string>
#include <vector>
#include <map>

namespace kajiiiro
{

// Uriを扱うクラス
class Uri
{
public:
    Uri();
    ~Uri();
    Uri(const Uri &copy) = delete;
    const Uri& operator=(const Uri &copy) = delete;
    bool setUri(const std::string &strUri);
    // scheme://host/resource?queryString
    const std::string& getScheme() const;
    const std::string& getHost() const;
    const std::vector<std::string>& getResource() const;
    const std::map<std::string, std::string>& getQueryString() const;
    const int& getPort() const;
private:
    std::string mStrScheme;
    std::string mStrHost;
    std::vector<std::string> mVecStrResource;
    std::map<std::string, std::string> mQueryString;
    int miPort;
    // URIから必要な情報を探す
    std::string::size_type FindScheme(const std::string &strUri);
    std::string::size_type FindHost(const std::string &strUri);
    std::string::size_type FindResource(const std::string &strUri);
    std::string::size_type FindQueryString(const std::string &strUri);
};


}; // namespace
