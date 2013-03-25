#ifndef KAJIIIRO_SERVER_H
#define KAJIIIRO_SERVER_H

#include <string>

const int SERVER_SUCCESS = 0;
const int SERVER_ERROR = 1;

class kajiiiro_server
{
public:
    int start(std::string& str_msg);
};

#endif // KAJIIIRO_SERVER_H
