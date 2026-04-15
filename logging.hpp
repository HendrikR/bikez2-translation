#pragma once

#include <iostream>
#include <sstream>
#include <cstdarg>

class Logger {
public:
    enum LogLevel { FATAL, ERROR, WARN, INFO, DEBUG, TRACE };
private:
    std::ostream& stream;
    LogLevel loglevel;
    char buffer[4096];
    void log2(LogLevel level, const char* format, va_list args) {
        if (level <= this->loglevel) {
            vsprintf(buffer, format, args);
            stream << buffer << std::endl;
        }
    }
public:
    Logger(std::ostream& _stream, LogLevel _loglevel = INFO)
        : stream(_stream), loglevel(_loglevel)
        {}
    void setLevel();
    void log(LogLevel level, const char* format, ...) {
        if (level <= this->loglevel) {
            std::va_list args;
            va_start(args, format);
            vsprintf(buffer, format, args);
            va_end(args);
            stream << buffer << std::endl;
        }
    }
    void fatal(const char* format, ...) { std::va_list a; va_start(a, format); va_end(a); log2(LogLevel::FATAL, format, a); }
    void error(const char* format, ...) { std::va_list a; va_start(a, format); va_end(a); log2(LogLevel::ERROR, format, a); }
    void warn (const char* format, ...) { std::va_list a; va_start(a, format); va_end(a); log2(LogLevel::WARN, format, a);  }
    void info (const char* format, ...) { std::va_list a; va_start(a, format); va_end(a); log2(LogLevel::INFO, format, a);  }
    void debug(const char* format, ...) { std::va_list a; va_start(a, format); va_end(a); log2(LogLevel::DEBUG, format, a); }
    void trace(const char* format, ...) { std::va_list a; va_start(a, format); va_end(a); log2(LogLevel::TRACE, format, a); }
    
};
