#include "udp-net/socket.h"
#include "udp-net/logger.h"
#include "udp-net/addresses.h"
#include "udp-net/defs.h"

#include <sys/socket.h>
#include <arpa/inet.h>

int create_socket_v4(){
    int fd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if(fd < 0){
        sys_log_exit("socket cretion failure");
    }

    return fd;
}

void bind_socket_to_any_v4(int fd){
    struct sockaddr_in addr_in;
    init_any_addr_v4(&addr_in, APP_PORT);

    struct sockaddr *addr = (struct sockaddr *)&addr_in;

    if(bind(fd, addr, sizeof(addr_in)) < 0){
        sys_log_exit("socket binding failure");
    }
}