#include "udp-net.h"
#include <stdio.h>

int main(){
    Server s;
    init_server(&s);
    set_server_socket(&s);
    bind_server_socket(&s);

    print_server_addrs();

    while (s.running){        
    }
    
    close_server(&s);
    return 0;
}