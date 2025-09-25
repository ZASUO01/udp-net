#include "udp-net.h"
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <arpa/inet.h>

int main(int argc, char *argv[]){
    Params p = parse_args(argc, argv);

    set_log_level(LOG_INFO);

    if(p.mode == SERVER_MODE){
        init_server();
        
        set_server_socket();
        
        bind_server_socket();
        
        init_server_threads();
        
        start_sever();
        
        print_server_addrs();
   
        read_inputs();

        join_server_threads();

        close_server();
    }else if(p.mode == CLIENT_MODE){
       init_client();
       set_client_socket();

       char input[INET_ADDRSTRLEN];
       read_server_ip_from_terminal(input, INET_ADDRSTRLEN);

       add_server_addr_to_client(input);

       start_handshake();

       close_client();
    }

    
    return 0;
}