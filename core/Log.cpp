#include "Log.hpp"
#include <chrono>
#include <iomanip>
#include <sstream>
#include <thread>
#include "pch.hpp"

#ifdef _WIN32
#include <windows.h>
#include <io.h>
#else
#include <unistd.h>
#include <pthread.h>
#endif

namespace LogColors {
    const char* c_reset = "\033[0m";
    const char* c_bold = "\033[1m";

    const char* c_debug = "\033[36m";         // Cyan
    const char* c_info = "\033[32m";          // Green  
    const char* c_warning = "\033[33m";       // Yellow
    const char* c_error = "\033[31m";         // Red
    const char* c_critical = "\033[1;31m";    // Bold Red

    const char* c_timestamp = "\033[90m";     // Dark Gray
    const char* c_service = "\033[94m";       // Light Blue
    const char* c_file = "\033[35m";          // Magenta
}

int getProcessId() {
#ifdef _WIN32
    return static_cast<int>(GetCurrentProcessId());
#else
    return static_cast<int>(getpid());
#endif
}

std::string getTimestamp() {
    using namespace std::chrono;
    auto now = system_clock::now();
    auto ms = duration_cast<milliseconds>(now.time_since_epoch()) % 1000;
    std::time_t t = system_clock::to_time_t(now);
    std::tm utc_tm{};

#ifdef _WIN32
    gmtime_s(&utc_tm, &t);
#else
    gmtime_r(&t, &utc_tm);
#endif

    std::ostringstream oss;
    oss << std::put_time(&utc_tm, "%Y:%m:%dT%H:%M:%S")
        << '.' << std::setw(3) << std::setfill('0') << ms.count()
        << 'Z';
    return oss.str();
}

std::string extractFilename(const char* filepath) {
    if (!filepath) return "unknown";

    std::string path(filepath);
    size_t pos = path.find_last_of("/\\");
    if (pos != std::string::npos) {
        return path.substr(pos + 1);
    }
    return path;
}

namespace Log {

    const char* getLevelColor(ELogLevels level) {
        switch (level) {
        case l_debug: return LogColors::c_debug;
        case l_info: return LogColors::c_info;
        case l_warning: return LogColors::c_warning;
        case l_error: return LogColors::c_error;
        case l_critical: return LogColors::c_critical;
        default: return LogColors::c_reset;
        }
    }

    bool supportsColors() {
#ifdef _WIN32
        HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
        if (hOut == INVALID_HANDLE_VALUE) return false;

        DWORD dwMode = 0;
        if (!GetConsoleMode(hOut, &dwMode)) return false;

        dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
        return SetConsoleMode(hOut, dwMode);
#else
        return isatty(STDOUT_FILENO);
#endif
    }

    void log_processor(const std::string& message, ELogLevels level,
        const char* service_name, const char* file, int line) {

        static bool colorsEnabled = supportsColors();

        if (colorsEnabled) {
            std::cout << getLevelColor(level) << char(level) << LogColors::c_reset
                << ":" << LogColors::c_timestamp << getTimestamp() << LogColors::c_reset
                << ":t" << getProcessId();

            if (service_name) {
                std::cout << ":" << LogColors::c_service << "[" << service_name << "]" << LogColors::c_reset;
            }

            if (file && line > 0) {
                std::cout << LogColors::c_file << "{" << extractFilename(file) << ":" << line << "}" << LogColors::c_reset;
            }

            std::cout << " " << message << std::endl;
        }
        else {
            std::cout << char(level)
                << ":" << getTimestamp()
                << ":t" << getProcessId();

            if (service_name) {
                std::cout << ":[" << service_name << "]";
            }

            if (file && line > 0) {
                std::cout << "{" << extractFilename(file) << ":" << line << "}";
            }

            std::cout << " " << message << std::endl;
        }
    }

    void I(const std::string& message, const char* service_name,
        const char* file, int line) {
        log_processor(message, ELogLevels::l_info, service_name, file, line);
    }

    void W(const std::string& message, const char* service_name,
        const char* file, int line) {
        log_processor(message, ELogLevels::l_warning, service_name, file, line);
    }

    void E(const std::string& message, const char* service_name,
        const char* file, int line) {
        log_processor(message, ELogLevels::l_error, service_name, file, line);
    }

    void C(const std::string& message, const char* service_name,
        const char* file, int line) {
        log_processor(message, ELogLevels::l_critical, service_name, file, line);
    }

    void D(const std::string& message, const char* service_name,
        const char* file, int line) {
        log_processor(message, ELogLevels::l_debug, service_name, file, line);
    }
}