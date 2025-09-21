/**
 * @file logger.h
 * @brief Useful logger functions
 * @author ZASUO01
 */
#ifndef LOGGER_H
#define LOGGER_H

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

#endif