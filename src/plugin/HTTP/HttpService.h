#pragma once
#include <string>
// #include <plugin/Log/Log.h>

using std::string;


class HttpService_
{
private:
    // string ip = "127.0.0.1";
    // int port = 8084;
public:
    static string post_request(string& path, string& body);
    static string get_request(string& path);
};
