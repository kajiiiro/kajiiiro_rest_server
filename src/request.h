#pragma once

#include <string>
#include <vector>
#include <map>

namespace kajiiiro
{

class Request
{
public:
    Request();
    ~Request();
    Request(const Request &copy) = delete;
    const Request& operator=(const Request &copy) = delete;
    void setRequest(const std::string &strRequest);
    const std::string& getMethod() const;
    const std::vector<std::string>& getResource() const;
	const std::string& getBody() const;
	const std::map<std::string, std::string>& getOtherHeader() const;

private:
    class impl;
    impl *pImpl;
};

}; // namespace
