#pragma once

namespace kajiiiro
{

// Uriを扱うクラス
class Session
{
public:
    Session();
    ~Session();
    Session(const Session &copy) = delete;
    const Session& operator=(const Session &copy) = delete;
    bool startAccept(int iPort);
private:
	class impl;
	impl *pImpl;
};


}; // namespace
