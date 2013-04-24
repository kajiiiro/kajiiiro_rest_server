#include "define.h"
#include "helper.h"
#include "request.h"

namespace kajiiiro
{

class Request::impl
{
public:
	impl(const int &iClientFD) : mClientFD(iClientFD)
	{
	
	}
	std::string mStrRequest;
	std::string mStrMethod;
	std::string mStrBody;
	std::map<std::string, std::string> mOtherHeader;
	std::vector<std::string> mVecResource;
	int mClientFD;
};

Request::Request(const int &iClientFD) : pImpl(new Request::impl(iClientFD))
{

}

Request::~Request()
{
	delete pImpl;
}

int Request::getClient() const
{
	return pImpl->mClientFD;
}

std::string Request::getRequest() const
{
	return pImpl->mStrRequest;
}

void Request::setRequest(const std::string &strRequest)
{
	P("Request::setRequest start");
	pImpl->mStrRequest = strRequest;
	// まずはBodyとHeaderに分割
	P("divide request");
	Helper helper;
	pImpl->mStrBody = helper.getAfterKeyWord(strRequest, HTTP_BODY_DELIMITER);
	std::string strHeader = helper.getBeforeKeyWord(strRequest, HTTP_BODY_DELIMITER);
	// Headerを一行づつ分割
	P("divide header");
	std::vector<std::string> vecHeader;
	helper.splitStringList(strHeader, LINE_DELIMITER, vecHeader);
	bool bFirstFlg = true;
	P("get header information");
	FOR(vecHeader)
	{
		// 一行目に関してはメソッド等を取得する
		if (bFirstFlg)
		{
			bFirstFlg = false;
			pImpl->mStrMethod = helper.getBeforeKeyWord(*it, HTTP_FIRST_HEADER_DELIMITER);
			std::string strResource = helper.getAfterKeyWord(*it, HTTP_FIRST_HEADER_DELIMITER);
			// 後ろのHTTP/1.1とかはいらないので削除
			strResource = helper.getBeforeKeyWord(strResource, HTTP_FIRST_HEADER_DELIMITER);
			helper.splitStringList(strResource, RESOUSE_DELIMITER, pImpl->mVecResource);
			continue;
		}
		pImpl->mOtherHeader.insert(std::pair<std::string, std::string>(
			helper.getBeforeKeyWord(*it, HTTP_HEADER_DELIMITER)
			, helper.trimWhiteSpace(helper.getAfterKeyWord(*it, HTTP_HEADER_DELIMITER))
			));
	}
}

const std::string& Request::getMethod() const
{
	return pImpl->mStrMethod;
}

const std::vector<std::string>& Request::getResource() const
{
	return pImpl->mVecResource;
}

const std::string& Request::getBody() const
{
	return pImpl->mStrBody;
}

const std::map<std::string, std::string>& Request::getOtherHeader() const
{
	return pImpl->mOtherHeader;
}

}; // namespace
