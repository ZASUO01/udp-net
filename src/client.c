#include "udp-net/client.h"
#include "udp-net/socket.h"
#include "udp-net/logger.h"
#include "udp-net/addresses.h"
#include "udp-net/defs.h"
#include "udp-net/packet.h"

#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>

Client client;

void init_client(){
    client.connected = 0;
    client.sock_fd = -1;
}

void set_client_socket(){
    if(client.connected == 0){
        client.sock_fd = create_socket_v4();
    }
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
    if(client.connected == 0){
        struct sockaddr_in server_addr;

        if(parse_addr_v4(ip, &server_addr, APP_PORT) != 0){
            log_exit("invalid server addr");
        }

        client.server_addr = server_addr;
    }
}

void start_handshake(){
    if(client.connected == 0){
        UdpNetPacket req;
        init_packet(&req, 0, REQ_FLAG);
        build_packet(&req);
        
        size_t req_size = PACKET_HEADER_BYTES;

        if(send_packet_to_v4(client.sock_fd, &req, req_size, &client.server_addr) != 0){
            log_exit("failed to send request\n");
        }

        client.connected = 1;
    }
    
}

void close_client(){
    if(client.connected == 1){
        client.connected = 0;
    
        if(close(client.sock_fd) < 0){
            sys_log_exit("socket closure failure");
        }
    }
}


