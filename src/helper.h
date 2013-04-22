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
	// key_wordがない場合は空を返す
	std::string getBeforeKeyWord(const std::string& str, const std::string& key_word);
	// key_wordがない場合は空を返す
	std::string getAfterKeyWord(const std::string& str, const std::string& key_word);
};


}; // namespace
