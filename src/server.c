#include "udp-net/server.h"
#include "udp-net/socket.h"
#include "udp-net/logger.h"

#include <unistd.h>

void init_server(Server *s){
    s->running = 0;
    s->sock_fd = -1;
}

void set_server_socket(Server *s){
    s->sock_fd = create_socket_v4();
}

void bind_server_socket(Server *s){
    bind_socket_to_any_v4(s->sock_fd);
    s->running = 1;
}

void close_server(Server *s){
    if(close(s->sock_fd) < 0){
        sys_log_exit("socket closure failure");
    }
}