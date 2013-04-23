#pragma once

#include <iostream>
#include <string>

namespace kajiiiro
{

// defineは名前空間を持たないので好きではないが、
// 唯一認めているのは、以下のcoutを有意義に使用する方法

#define P(message) std::cout << message << std::endl
#define E(message) std::cerr << "[ERROR]" << message << std::endl

// 以下もわざわざコールバック作るの面倒だから定義しちゃう
// stl roop
#define FOR(stl) for (auto it = stl.begin();it != stl.end();++it)
// stl debug print
#define FOR_P(stl) for (auto it = stl.begin();it != stl.end();++it) P("[" << *it << "]")

// 文字列定義
const std::string WHITESPACE(" ");

const std::string HOST_DELIMITER("/");
const std::string RESOUSE_DELIMITER("/");
const std::string SCHEME_DELIMITER(":");
const std::string PORT_DELIMITER(":");
const std::string QUERY_STRING_START_DELIMITER("?");
const std::string QUERY_STRING_DELIMITER("&");
const std::string QUERY_STRING_VALUE_DELIMITER("=");
const std::string HTTP_HEADER_DELIMITER(":");
const std::string HTTP_FIRST_HEADER_DELIMITER(" ");
const std::string LINE_DELIMITER("\r\n");
const std::string HTTP_BODY_DELIMITER(LINE_DELIMITER + LINE_DELIMITER);
const std::string HTTP_METHOD_GET("GET");
const std::string HTTP_METHOD_PUT("PUT");
const std::string HTTP_METHOD_POST("POST");
const std::string HTTP_METHOD_DELETE("DELETE");

const std::string HTTP_VERSION("HTTP/1.1");
const std::string STATUSCODEWORD_200("200 OK");
const std::string STATUSCODEWORD_201("201 Created");
const std::string STATUSCODEWORD_204("204 No Content");
const std::string STATUSCODEWORD_303("303 See Other");
const std::string STATUSCODEWORD_400("400 Bad Request");
const std::string STATUSCODEWORD_403("403 Forbidden");
const std::string STATUSCODEWORD_404("404 Not Found");
const std::string STATUSCODEWORD_405("405 Method Not Allowed");
const std::string STATUSCODEWORD_500("500 Internal Server Error");

const std::string HTTP_HEADER_CONTENT_LENGTH("Content-Length");
const std::string HTTP_HEADER_TRANSFOR_ENCODING(std::string("Transfer-Encoding: chunked") + LINE_DELIMITER);

const std::string SERVER_PORT("port");

}; // namespace
