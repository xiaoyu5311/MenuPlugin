#pragma once
#include <nlohmann/json.hpp>
#include <plugin/Log/Log.h>
using nlohmann::json;

class JsonHelper
{
public:
    static json get_data(std::string& res)
    {
        json jsonData = json::parse(res.c_str());
        json data = jsonData["data"];
        return data;
    }
};
