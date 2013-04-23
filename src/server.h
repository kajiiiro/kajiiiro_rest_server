#pragma once

#include <string>

namespace kajiiiro
{

class Listener;

class Server
{
public:
	Server();
	~Server();
	Server(const Server &copy) = delete;
	const Server& operator=(const Server &copy) = delete;
	bool start(const int iPort = 7766);
	// メモリもServerクラスのデストラクタ内部で解放する
	bool setListener(Listener *listener);

private:
	class impl;
	impl *pImpl;
};


}; // namespace
