#include "udp-net/logger.h"

#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <stdio.h>

LogLevel current_log_level = LOG_DISABLED;

void set_log_level(LogLevel level){
    current_log_level = level;
}

void sys_log_exit(const char *msg){
    int err = errno;
    fprintf(stderr, "[SYSCALL ERROR] %s: %s\n", msg, strerror(err));
    exit(EXIT_FAILURE);
}

void log_exit(const char *msg){
    fprintf(stderr, "%s\n", msg);
    exit(EXIT_FAILURE);
}

void usage(const char *program){
    fprintf(stderr, "Usage:\n");
    fprintf(stderr, "%s mode: [1, 2]\n", program);
    exit(EXIT_FAILURE);
}