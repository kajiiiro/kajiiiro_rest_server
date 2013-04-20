#pragma once

namespace kajiiiro
{

class Db;

// Uriを扱うクラス
class Server
{
public:
    Server();
    ~Server();
    Server(const Server &copy) = delete;
    const Server& operator=(const Server &copy) = delete;
    bool start(const Db &config);
	//void addListener();
private:
	class impl;
	impl *pImpl;
};


}; // namespace
