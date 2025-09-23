#include "udp-net.h"
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <arpa/inet.h>

int main(int argc, char *argv[]){
    Params p = parse_args(argc, argv);

    if(p.mode == SERVER_MODE){
        init_server();
        set_server_socket();
        bind_server_socket();

        print_server_addrs();
   
        int *sock = malloc(sizeof(int));
        *sock = server.sock_fd;

        pthread_t recv_t;
        if(pthread_create(&recv_t, NULL, receive_data, sock) != 0){
            sys_log_exit("create receive thread");
        }

        read_inputs();

        if(pthread_join(recv_t, NULL) != 0){
            sys_log_exit("join receive thread");
        }

        close_server();
    }else if(p.mode == CLIENT_MODE){
       init_client();
       set_client_socket();

       char input[INET_ADDRSTRLEN];
       read_server_ip_from_terminal(input, INET_ADDRSTRLEN);

       add_server_addr_to_client(input);

       close_client();
    }

    
    return 0;
}