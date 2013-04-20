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
	class impl;
	impl *pImpl;
};


}; // namespace
