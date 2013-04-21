#include "helper.h"

namespace kajiiiro
{

bool Helper::splitStringList(const std::string& str_list
                     , const std::string& str_delimiter
                     , std::vector<std::string>& vec_str)
{
    if (("" == str_list) || ("" == str_delimiter)) return false;
    std::string tmp = this->trimWhiteSpace(str_list);
    std::string::size_type si_current = 0;
    std::string::size_type si_found   = 0;
    while (std::string::npos != (si_found = tmp.find(str_delimiter, si_current)))
    {
    	// 区切りが連続した場合は空をいれてしまうので、それを確認後に挿入する
    	if ("" != tmp.substr(si_current, si_found - si_current))
    		vec_str.push_back(tmp.substr(si_current, si_found - si_current));
        si_current = si_found + str_delimiter.size();
    }
    vec_str.push_back(tmp.substr(si_current));
    return true;
}

std::string Helper::trimWhiteSpace(const std::string& str)
{
	std::string::size_type start;
	for (std::string::size_type i = 0;i < str.size();++i)
	{
		if (' ' != str.at(i))
		{
			start = i;
			break;
		}
	}
	std::string::size_type end;
	for (std::string::size_type i = str.size() - 1;0 <= i;--i)
	{
		if (' ' != str.at(i))
		{
			end = i;
			break;
		}
	}
	return str.substr(start, end - start + 1);
}

}; // namespace
