#pragma once
#include "pch.hpp"

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