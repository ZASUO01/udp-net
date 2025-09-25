/**
 * @file logger.h
 * @brief Useful logger functions
 * @author ZASUO01
 */
#ifndef LOGGER_H
#define LOGGER_H

#include <stdio.h>

typedef enum {
    LOG_DISABLED,
    LOG_ERROR,
    LOG_WARN,
    LOG_INFO,
    LOG_DEBUG
} LogLevel;

/** @brief Global logger log level*/
extern LogLevel current_log_level;

/** Macro to print formatted logs */
#define LOG_MSG(level, fmt, ...) \
    do { \
        if((level) <= current_log_level && (level) > LOG_DISABLED) { \
            static const char * level_names[] = {"NONE","ERROR", "WARNING", "INFO", "DEBUG"}; \
            if((level) == LOG_ERROR){ \
                fprintf(stderr, "(%s : %d) ", \
                __FILE__, __LINE__); \
            } \
            fprintf(stderr, "[%s] " fmt "\n", \
                level_names[level], ##__VA_ARGS__); \
        } \
    } while(0);


/**
 * @brief Set the global log level.
 * @param level The log level. Use LOG_DISABLED, LOG_ERROR, LOG_WARN, LOG_INFO, LOG_DEBUG.
 */
void set_log_level(LogLevel level);

/**
 * @brief Captures the system call error, logs the message and exit with failure
 * @param msg The message to be displayed
 */
void sys_log_exit(const char *msg);

/**
 * @brief Logs the message and exit with failure
 * @param msg The message to be displayed
 */
void log_exit(const char *msg);

/** @brief Print the correct program usage with expected command line arguments */
void usage(const char *program);

#endif