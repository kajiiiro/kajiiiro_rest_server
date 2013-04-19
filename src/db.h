#pragma once

#include <string>
#include <map>
#include <tuple>

namespace kajiiiro
{

class Db
{
public:
    Db();
    ~Db();
    Db(const Db &copy) = delete;
    const Db& operator=(const Db &copy) = delete;
    void addValue(const std::string &strKey, const std::string &strValue);
    void addValue(const std::string &strKey, const int &iValue);
    void addValue(const std::string &strKey, const double &dValue);
    // keyが存在しない場合はfalseを返す
    bool getValue(const std::string &strKey, std::string &strValue) const;
    bool getValue(const std::string &strKey, int &iValue) const;
    bool getValue(const std::string &strKey, double &dValue) const;
private:
    std::map< std::string, std::tuple<std::string, int, double> > *mpKeyValue;
    void addValue(const std::string &strKey
                  , const std::string &strValue
                  , const int &iValue
                  , const double &dValue);
};


}; // namespace
