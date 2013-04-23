#include <string>
#include <vector>
#include <map>

#include "define.h"
#include "request.h"
#include "response.h"
#include "session.h"
#include "listener.h"
#include "sampleListener.h"

using namespace std;

namespace kajiiiro
{

class SampleRestListener::impl
{
public:
	vector<string> mResource;
	// 作成するリソースのインデックスで管理する
	map<string::size_type, string> mHtml;
	// リソースの存在確認
	bool existResource(const vector<string> vecRequestResource)
	{
		// 本当のリソースよりもおおきければエラー
		if (mResource.size() < vecRequestResource.size())
		{
			return false;
		}
		// 確かめる方でループを回し、すべて一致していればOK
		for (string::size_type i = 0;i < vecRequestResource.size();++i)
		{
			if (mResource[i] != vecRequestResource[i])
			{
				return false;
			}
		}
		return true;
	}
	bool existResource4Post(const vector<string> vecPostResource)
	{
		// ポストはリソースを指定して送ることとする
		if (vecPostResource.size() < mResource.size())
		{
			return false;
		}
		// またリソースは一つづつ作成することとする
		if (vecPostResource.size() != mResource.size() + 1)
		{
			return false;
		}
		for (string::size_type i = 0;i < mResource.size();++i)
		{
			if (mResource[i] != vecPostResource[i])
			{
				return false;
			}
		}
		return true;
	}
	bool existResource4Delete(const vector<string> vecDeleteResource)
	{
		// 削除はリソースが最大のものと一致することとする
		if (vecDeleteResource.size() != mResource.size())
		{
			return false;
		}
		// 確かめる方でループを回し、すべて一致していればOK
		for (string::size_type i = 0;i < vecDeleteResource.size();++i)
		{
			if (mResource[i] != vecDeleteResource[i])
			{
				return false;
			}
		}
		return true;
	}
};

SampleRestListener::SampleRestListener() : pImpl(new impl())
{
	// 始めにtestリソースを作成しておく
	pImpl->mResource.push_back("test");
	// 添字は何でもいいけど、0からにしておく
	pImpl->mHtml.insert(pair<int, string>(pImpl->mResource.size() - 1, "<h1>this is sample page.</h1>"));
}

SampleRestListener::~SampleRestListener()
{
	delete pImpl;
}

void SampleRestListener::doGet(const Request &request, Response &response, Session &session)
{
	if (false == pImpl->existResource(request.getResource()))
	{
		response.setStatusCode(404);
		session.sendMessage(response);
		return;
	}
	else
	{
		response.setStatusCode(200);
		response.setBody(pImpl->mHtml[request.getResource().size() - 1]);
		session.sendMessage(response);
	}
	session.disconnectSession(response);
}

void SampleRestListener::doPut(const Request &request, Response &response, Session &session)
{
	if (false == pImpl->existResource(request.getResource()))
	{
		response.setStatusCode(404);
		session.sendMessage(response);
	}
	else
	{
		pImpl->mHtml[request.getResource().size() - 1] = request.getBody();
		response.setStatusCode(204);
		session.sendMessage(response);
	}
	session.disconnectSession(response);
}

void SampleRestListener::doPost(const Request &request, Response &response, Session &session)
{
	if (false == pImpl->existResource4Post(request.getResource()))
	{
		response.setStatusCode(400); // 500?
		session.sendMessage(response);
		return;
	}
	else
	{
		pImpl->mHtml[request.getResource().size() - 1] = request.getBody();
		response.setStatusCode(201);
		session.sendMessage(response);
	}
	session.disconnectSession(response);
}

void SampleRestListener::doDelete(const Request &request, Response &response, Session &session)
{
	if (false == pImpl->existResource4Delete(request.getResource()))
	{
		response.setStatusCode(400); // 500?
		session.sendMessage(response);
		return;
	}
	else
	{
		// リソースと要素を削除
		auto it = pImpl->mHtml.find(request.getResource().size() - 1);
		pImpl->mHtml.erase(it);
		pImpl->mResource.pop_back();
		response.setStatusCode(204);
		session.sendMessage(response);
	}
	session.disconnectSession(response);
}

}; // namespace
