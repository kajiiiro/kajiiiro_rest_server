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
    // 両端の空白を取り除く
    std::string trimWhiteSpace(const std::string& str);
};


}; // namespace
