#include "udp-net/server.h"
#include "udp-net/defs.h"
#include "udp-net/packet.h"
#include "udp-net/socket.h"
#include "udp-net/addresses.h"
#include "udp-net/logger.h"

#include <stdio.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

Server server;

static char *read_line();
static void *receive_data(void *arg);

void init_server(){
    server.running = 0;
    server.sock_fd = -1;
    pthread_mutex_init(&server.server_mutex, NULL);
}

void set_server_socket(){
    if(server.running == 0){
        server.sock_fd = create_socket_v4();
    }
}

void bind_server_socket(){
    if(server.running == 0){
        bind_socket_to_any_v4(server.sock_fd);
    }
}

void start_sever(){
    if(server.running == 0){
        server.running = 1;
    }
}

void print_server_addrs(){
  printf("Server Running\n");
  printf("PORT: %d\n", APP_PORT);
  printf("LOCAL IP: 127.0.0.1\n");

  char *ip = get_public_lan_ip_v4();
  printf("PUBLIC IP: %s\n", ip);

  free(ip);
}

void init_server_threads(){
    if(server.running == 0){
        int *sock = malloc(sizeof(int));
        *sock = server.sock_fd;

        if(pthread_create(&server.receive_t, NULL, receive_data, sock) != 0){
            sys_log_exit("create receive thread");
        }    
    }
}


void join_server_threads(){
    if(server.running == 1){
        if(pthread_join(server.receive_t, NULL) != 0){
            sys_log_exit("join receive thread");
        }
    }
}

void read_inputs(){
    while(server.running){
        printf("> ");
        fflush(stdout);

        char *line = read_line();
        if (line == NULL) {
            continue;
        }

        if (strlen(line) == 0) {
            continue;
        }
        
        if(strcmp(line, "quit") == 0){
            printf("closing the server...\n");
            server.running = 0;
        }
    }
}

void close_server(){
    if(server.running == 1){
        server.running = 0;

        pthread_mutex_destroy(&server.server_mutex);

        if(close(server.sock_fd) < 0){
            sys_log_exit("socket closure failure");
        }
    }
}

static char *read_line(){
    static char input[MAX_INPUT_SIZE];
    
    if (fgets(input, sizeof(input), stdin) == NULL) {
        return NULL;
    }

    input[strcspn(input, "\n")] = '\0';

    return input;
}

static void *receive_data(void *arg){
    LOG_MSG(LOG_INFO, "start receiving thread");

    int socket = *(int *)arg;
    free(arg);

    while(1){
        pthread_mutex_lock(&server.server_mutex);
        if(server.running == 0){
            pthread_mutex_unlock(&server.server_mutex);
            break;
        } 
        pthread_mutex_unlock(&server.server_mutex);

        if(socket_ready_to_receive(socket) != 0){
            continue;
        }

        UdpNetPacket pk;
        struct sockaddr_in client_addr;

        if(receive_packet_from_v4(socket, &pk, &client_addr) != 0){
            continue;
        }

        if(is_valid_packet(&pk) != 0){
            continue;
        }

        switch (pk.flag){
        case REQ_FLAG:
            printf("req\n");
            break;
        case ACC_FLAG:
            printf("acc\n");
            break;
        case ACK_FLAG:
            printf("ack\n");
            break;
        case DATA_FLAG:
            printf("data\n");
            break;
        case END_FLAG:
            printf("end\n");
            break;
        case RST_FLAG:
            printf("reset flag\n");
            break;
        default:
            break;
        }
        
    }

    LOG_MSG(LOG_INFO, "stop receiving thread");
    return NULL;
}