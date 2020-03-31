#ifndef LOGGER_H
#define LOGGER_H

#include <string>
#include <cstring>
#include <cstdio>
#include <chrono>
#include <ctime>

#pragma GCC system_header

#define __FILENAME__ (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)
#define DEBUG_INFO 1
#define DEBUG_ERROR 1
#define DEBUG_WARNING 1
#define DEBUG_DBG 1
#define DEBUG_MESSAGE

static std::string current_time() {
    char timebuffer[100];
    std::time_t now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    std::time_t t = std::time(nullptr);
    std::size_t tlen = std::strftime(timebuffer, sizeof(timebuffer), "%F %T", std::localtime(&t));
    if (tlen == 0)
        return "";
    return std::string(timebuffer, tlen);
}

// with date, time, file:line
#define log_info(fmt, ...) \
    do { \
            if ( DEBUG_INFO) { \
                fprintf( stdout, "INFO: %s %s:%d: " fmt "\n", current_time().c_str(), __FILENAME__, __LINE__, ##__VA_ARGS__ ); \
            } \
       } while(0)

// with date, time, file:line
#define log_error(fmt, ...) \
    do { \
            if ( DEBUG_ERROR) { \
                fprintf( stderr, "ERROR: %s %s:%d: " fmt "\n", current_time().c_str(), __FILENAME__, __LINE__, ##__VA_ARGS__ ); \
            } \
       } while(0)

#define log_warning(fmt, ...) \
    do { \
            if ( DEBUG_WARNING) { \
                fprintf( stdout, "WARNING: %s %s:%d: " fmt "\n", current_time().c_str(), __FILENAME__, __LINE__, ##__VA_ARGS__ ); \
            } \
       } while(0)

// with date, time, file:line
#define log_debug(fmt, ...) \
    do { \
            if ( DEBUG_DBG) { \
                fprintf( stdout, "INFO: %s %s:%d: " fmt "\n", current_time().c_str(), __FILENAME__, __LINE__, ##__VA_ARGS__ ); \
            } \
       } while(0)

#endif // LOGGER_H
