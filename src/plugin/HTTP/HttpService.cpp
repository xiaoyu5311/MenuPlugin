#include "HttpService.h"

#include <plugin/Log/Log.h>

#include "httplib.h"

string HttpService_::post_request(string& path, string& body)
{
    httplib::Client cli("localhost", 8084);
    httplib::Headers headers = {
        {"Content-Type", "application/json"}
    };

    auto res = cli.Post(path, headers, body, "application/json");

    if (res && res->status == 200)
    {
        Log::Info(path + " :" + res->body);
        return res->body;
    }
    return "";
}

string HttpService_::get_request(string& path)
{
    httplib::Client cli("localhost", 8084);
    Log::Info("path   :" + path);

    auto res = cli.Get(path);
    if (res && res->status == 200)
    {
        Log::Info(path + " :" + res->body);
        return res->body;
    }
    return "";
}
