#pragma once

#include <chrono>
#include <iostream>
#include <optional>
#include <string>
#include <sstream>
#include <ctype.h>

class LogDuration {
public:
    explicit LogDuration(const std::string& msg = "")
            : message(msg + ": ")
            , start(std::chrono::steady_clock::now())
    {
    }

    ~LogDuration() {
        auto finish = std::chrono::steady_clock::now();
        auto dur = finish - start;
        std::ostringstream os;
        os << message
           << std::chrono::duration_cast<std::chrono::milliseconds>(dur).count()
           << " ms" << std::endl;
        std::cerr << os.str();
    }
private:
    std::string message;
    std::chrono::steady_clock::time_point start;
};

class TotalDuration {
private:
    std::string message_ {};
public:
    std::chrono::steady_clock::duration totalDuration_;
    TotalDuration() = default;
    explicit TotalDuration(std::string msg);
    ~TotalDuration();
};

class LocalDuration {
private:
    std::chrono::steady_clock::duration& clock_;
    std::chrono::steady_clock::time_point start_;
public:
    explicit LocalDuration(std::chrono::steady_clock::duration& clock);
    explicit LocalDuration(TotalDuration& clock);
    ~LocalDuration();
};
#ifndef UNIQ_ID
#define UNIQ_ID_IMPL(lineno) _a_local_var_##lineno
#define UNIQ_ID(lineno) UNIQ_ID_IMPL(lineno)
#endif

#define LOG_DURATION(message) \
  LogDuration UNIQ_ID(__LINE__){message};

#define LOCAL_DURATION(clock) \
  LocalDuration UNIQ_ID(__LINE__){clock};


