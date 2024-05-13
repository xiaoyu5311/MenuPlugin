#pragma once
#include <ll/api/Logger.h>

class Log {

public:
    static ll::Logger* logger;

    static void Init(ll::Logger* loggertem) {
        logger = loggertem;
    };

    static void Info(const std::string& info) {
        if (logger) {
            logger->info(info);
        }
    }

    static void Debug(const std::string& info) {
        if (logger) {
            logger->debug(info);
        }
    }

    static void Error(const std::string& info) {
        if (logger) {
            logger->error(info);
        }
    }
};


