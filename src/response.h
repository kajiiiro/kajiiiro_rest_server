#pragma once

#include <string>
#include <vector>
#include <map>

namespace kajiiiro
{

class Response
{
public:
	Response() = delete;
	// responseにクライアントのファイルディスクリプターを設定する
	Response(const int &iClientFD);
	~Response();
	Response(const Response &copy) = delete;
	const Response& operator=(const Response &copy) = delete;
	std::string getResponse() const;
	// 200以外のときは設定する
	void setStatusCode(const int &iStatusCode);
	// content lenghtおよびTransfor Encodingは設定しないこと
	void setOtherHeader(const std::map<std::string, std::string> &OtherHeader);
	// 通常送信の場合のメソッド chunked送信の場合エラーが返る
	bool setBody(const std::string &strBody);
	// chunked送信の場合のメソッド 通常送信の場合エラーが返る
	bool appendBody(const std::string &strBody);
	void setTransforEncoding(const bool &bChunked);

private:
	friend class Session;
	int getClient() const;
	class impl;
	impl *pImpl;
};

}; // namespace
