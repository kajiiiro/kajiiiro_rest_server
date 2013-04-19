#pragma once

#include <string>
#include <vector>

namespace kajiiiro
{

class Helper
{
public:
    bool splitStringList(const std::string& str_list
                         , const std::string& str_delimiter
                         , std::vector<std::string>& vec_str);
};


}; // namespace
