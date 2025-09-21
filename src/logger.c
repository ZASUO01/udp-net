#include "udp-net/logger.h"

#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <stdio.h>

void sys_log_exit(const char *msg){
    int err = errno;
    fprintf(stderr, "[SYSCALL ERROR] %s: %s\n", msg, strerror(err));
    exit(EXIT_FAILURE);
}

void log_exit(const char *msg){
    fprintf(stderr, "%s\n", msg);
    exit(EXIT_FAILURE);
}