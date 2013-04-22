#include "define.h"
#include "helper.h"
#include "uri.h"

namespace kajiiiro
{

class Uri::impl
{
public:
	impl() : miPort(-1)
	{
	}
	std::string mStrScheme;
	std::string mStrHost;
	std::vector<std::string> mVecStrResource;
	std::map<std::string, std::string> mQueryString;
	int miPort;
	// URIから必要な情報を探す
	std::string::size_type FindScheme(const std::string &strUri)
	{
		std::string::size_type location = strUri.find(SCHEME_DELIMITER);
		if (std::string::npos != location)
			mStrScheme = strUri.substr(0, location);
		return location;
	}
	std::string::size_type FindHost(const std::string &strUri)
	{
		std::string::size_type location = strUri.find(HOST_DELIMITER);
		std::string strHostPort;
		if (std::string::npos != location)
			strHostPort = strUri.substr(0, location);

		std::string::size_type tmp = strHostPort.find(PORT_DELIMITER);
		if (std::string::npos != tmp)
		{
			mStrHost = strHostPort.substr(0, tmp);
			miPort = atoi(strHostPort.substr(tmp + 1, location - (tmp + 1)).c_str());
		}
		else
		{
			// portがない場合はそのままをホストに設定
			mStrHost = strHostPort;
		}
		// /の位置を返す
		return location;
	}
	std::string::size_type FindResource(const std::string &strUri)
	{
		Helper helper;
		std::vector<std::string> vecResource;
		helper.splitStringList(strUri, RESOUSE_DELIMITER, vecResource);
		return strUri.find_last_of(RESOUSE_DELIMITER);
	}
	std::string::size_type FindQueryString(const std::string &strUri)
	{
		std::string::size_type location = strUri.find(QUERY_STRING_START_DELIMITER);
		std::string strQueryString;
		if (std::string::npos == location)
			return std::string::npos;
		// ?以降を取得
		strQueryString = strUri.substr(location + 1);
		Helper helper;
		std::vector<std::string> vecQueryString;
		helper.splitStringList(strQueryString, QUERY_STRING_DELIMITER, vecQueryString);
		std::string::size_type tmp = 0;
		for (auto it = vecQueryString.begin();it != vecQueryString.end();++it)
		{
			tmp = it->find(QUERY_STRING_VALUE_DELIMITER);
			if (std::string::npos != tmp)
				mQueryString.insert(std::pair<std::string, std::string>(
						it->substr(0, tmp)
						, it->substr(tmp + 1)));
		}
		// 返すのは?の位置
		return location;
	}
};

Uri::Uri() : pImpl(new Uri::impl())
{

}

Uri::~Uri()
{
	delete pImpl;
}

bool Uri::setUri(const std::string &strUri)
{
	std::string strTmp = strUri;
	std::string::size_type string_length = pImpl->FindQueryString(strTmp);
	if (std::string::npos == string_length)
		return false;
	// ?以降は切り取り
	strTmp = strTmp.substr(0, string_length);

	string_length = pImpl->FindScheme(strTmp);
	if (std::string::npos == string_length)
		return false;
	// ://以降を渡す
	strTmp = strTmp.substr(string_length + 3);

	string_length = pImpl->FindHost(strTmp);
	if (std::string::npos == string_length)
		return false;
	// /以降を渡す
	strTmp = strTmp.substr(string_length + 1);

	string_length = pImpl->FindResource(strTmp);
	if (std::string::npos == string_length)
		return false;
	return true;
}

const std::string& Uri::getScheme() const
{
	return pImpl->mStrScheme;
}

const std::string& Uri::getHost() const
{
	return pImpl->mStrHost;
}

const std::vector<std::string> &Uri::getResource() const
{
	return pImpl->mVecStrResource;
}

const std::map<std::string, std::string>& Uri::getQueryString() const
{
	return pImpl->mQueryString;
}

const int& Uri::getPort() const
{
	return pImpl->miPort;
}

}; // namespace
