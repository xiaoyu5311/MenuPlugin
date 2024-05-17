#pragma once
#include <plugin/Log/Log.h>

#include "http/PostMethod.h"


#include "http/HttpClient.h"
using namespace std;

class HttpService_
{
private:
    string ip = "127.0.0.1";
    int port = 8084;

    ResponseCallback http_callback=nullptr;
    HttpClient* http_client_;

public:
    ~ HttpService_()
    {
        delete http_client_;
    }

    explicit HttpService_(string ip, int port): ip(ip), port(port), http_client_(nullptr)
    {
        http_client_ = new HttpClient(ip, port);
    }

    HttpService_(): http_client_(nullptr)
    {
    }

    void Post(string relative, string json, ResponseCallback http_callback_local)
    {
        PostMethod post_method{relative, json, http_callback_local};
        http_client_->executeMethod(&post_method);
    }


    void Get()
    {
        // if (resp == NULL)
        // {
        //     Log::Error("request failed!");
        // }
        // else
        // {
        //     Log::Debug(resp->body.c_str());
        // }


        // // 创建 HttpClient 实例
        // HttpClient client;
        //
        // // 创建 HttpRequest 实例
        // HttpRequestPtr req(new HttpRequest);
        // req->method = HTTP_GET;
        // req->url = url; // 目标URL
        //
        // // 设置响应回调
        // auto callback = [](const HttpResponsePtr& resp)
        // {
        //     if (resp)
        //     {
        //         // 输出响应状态码和响应体
        //         std::cout << "Status: " << resp->status_code << std::endl;
        //         std::cout << "Body: " << resp->body << std::endl;
        //     }
        //     else
        //     {
        //         std::cerr << "Request failed!" << std::endl;
        //     }
        // };
        //
        // // 发送异步请求
        // client.sendAsync(req, callback);
        //
        // while (true)
        // {
        //     
        // }
    }
};
