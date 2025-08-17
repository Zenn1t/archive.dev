#pragma once
#include "pch.hpp"
#include <sstream>

enum ELogLevels {
    l_info = 'I',
    l_warning = 'W',
    l_error = 'E',
    l_critical = 'C',
    l_debug = 'D'
};

namespace LogColors {
    extern const char* c_reset;
    extern const char* c_bold;
    extern const char* c_debug;         // Cyan
    extern const char* c_info;          // Green  
    extern const char* c_warning;       // Yellow
    extern const char* c_error;         // Red
    extern const char* c_critical;      // Bold Red
    extern const char* c_timestamp;     // Dark Gray
    extern const char* c_service;       // Light Blue
    extern const char* c_file;          // Magenta
}

namespace Log {
    void log_processor(const std::string& message, ELogLevels level,
        const char* service_name = nullptr,
        const char* file = nullptr, int line = 0);

    /*Info Level*/
    void I(const std::string& message, const char* service_name = nullptr,
        const char* file = nullptr, int line = 0);
    /*Warning Level*/
    void W(const std::string& message, const char* service_name = nullptr,
        const char* file = nullptr, int line = 0);
    /*Error Level*/
    void E(const std::string& message, const char* service_name = nullptr,
        const char* file = nullptr, int line = 0);
    /*Critical Level*/
    void C(const std::string& message, const char* service_name = nullptr,
        const char* file = nullptr, int line = 0);
    /*Debug Level*/
    void D(const std::string& message, const char* service_name = nullptr,
        const char* file = nullptr, int line = 0);

    const char* getLevelColor(ELogLevels level);
    bool supportsColors();
}

#define LI(service, msg) Log::I(msg, service, __FILE__, __LINE__)
#define LW(service, msg) Log::W(msg, service, __FILE__, __LINE__)
#define LE(service, msg) Log::E(msg, service, __FILE__, __LINE__)
#define LC(service, msg) Log::C(msg, service, __FILE__, __LINE__)
#define LD(service, msg) Log::D(msg, service, __FILE__, __LINE__)

#ifndef SERVICE_NAME
#define SERVICE_NAME "unknown-service"
#endif

#define lI(msg) LI(SERVICE_NAME, msg)
#define lW(msg) LW(SERVICE_NAME, msg)
#define lE(msg) LE(SERVICE_NAME, msg)
#define lC(msg) LC(SERVICE_NAME, msg)
#define lD(msg) LD(SERVICE_NAME, msg)

namespace Log {
    template<typename T>
    void stream_helper(std::ostringstream& oss, T&& t) {
        oss << std::forward<T>(t);
    }

    template<typename T, typename... Args>
    void stream_helper(std::ostringstream& oss, T&& t, Args&&... args) {
        oss << std::forward<T>(t);
        stream_helper(oss, std::forward<Args>(args)...);
    }
}

#define LOG_STREAM(level, service, ...) do { \
    std::ostringstream _log_stream; \
    Log::stream_helper(_log_stream, __VA_ARGS__); \
    Log::level(_log_stream.str(), service, __FILE__, __LINE__); \
} while(0)

#define LI_V(service, ...) LOG_STREAM(I, service, __VA_ARGS__)
#define LW_V(service, ...) LOG_STREAM(W, service, __VA_ARGS__)
#define LE_V(service, ...) LOG_STREAM(E, service, __VA_ARGS__)
#define LC_V(service, ...) LOG_STREAM(C, service, __VA_ARGS__)
#define LD_V(service, ...) LOG_STREAM(D, service, __VA_ARGS__)

#define lI_v(...) LI_V(SERVICE_NAME, __VA_ARGS__)
#define lW_v(...) LW_V(SERVICE_NAME, __VA_ARGS__)
#define lE_v(...) LE_V(SERVICE_NAME, __VA_ARGS__)
#define lC_v(...) LC_V(SERVICE_NAME, __VA_ARGS__)
#define lD_v(...) LD_V(SERVICE_NAME, __VA_ARGS__)