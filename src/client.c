#include "udp-net/client.h"
#include "udp-net/socket.h"
#include "udp-net/logger.h"
#include "udp-net/addresses.h"
#include "udp-net/defs.h"

#include <unistd.h>
#include <stdio.h>
#include <string.h>

Client client;

void init_client(){
    client.connected = 0;
    client.sock_fd = -1;
}

void set_client_socket(){
    client.sock_fd = create_socket_v4();
}

void read_server_ip_from_terminal(char *buff, size_t buff_size){
    while(1){
        printf("Please type the server ip (or quit to exit): ");
        
        if (fgets(buff, buff_size, stdin) == NULL) {
            printf("invalid ip, try again...\n");
            continue;
        }

        buff[strcspn(buff, "\n")] = '\0';
    
        if (strcmp(buff, "q") == 0 || strcmp(buff, "quit") == 0) {
            close_client();
            log_exit("exit");
        }

        struct sockaddr_in temp;
        if(parse_addr_v4(buff, &temp, APP_PORT) != 0){
            printf("invalid ip, try again...\n");
            continue;
        }

        break;
    }
}


void add_server_addr_to_client(const char *ip){
    struct sockaddr_in server_addr;

    if(parse_addr_v4(ip, &server_addr, APP_PORT) != 0){
        log_exit("invalid server addr");
    }

    client.server_addr = server_addr;
}

void close_client(){
    if(close(client.sock_fd) < 0){
        sys_log_exit("socket closure failure");
    }
}


