#include "udp-net.h"
#include <stdio.h>

int main(){
    init_server();
    set_server_socket();
    bind_server_socket();

    print_server_addrs();

    read_inputs();

    close_server();
    return 0;
}