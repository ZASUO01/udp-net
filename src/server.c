#include "udp-net/server.h"
#include "udp-net/socket.h"
#include "udp-net/logger.h"
#include "udp-net/addresses.h"

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

Server server;

static char *read_line();

void init_server(){
    server.running = 0;
    server.sock_fd = -1;
}

void set_server_socket(){
    server.sock_fd = create_socket_v4();
}

void bind_server_socket(){
    bind_socket_to_any_v4(server.sock_fd);
    server.running = 1;
}

void print_server_addrs(){
  printf("Server Running\n");
  printf("PORT: %d\n", APP_PORT);
  printf("LOCAL IP: 127.0.0.1\n");

  char *ip = get_public_lan_ip_v4();
  printf("PUBLIC IP: %s\n", ip);

  free(ip);
}

void close_server(){
    if(close(server.sock_fd) < 0){
        sys_log_exit("socket closure failure");
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

void *receive_data(void){
    // TODO
    return NULL;
}

static char *read_line(){
    static char input[MAX_INPUT_SIZE];
    
    if (fgets(input, sizeof(input), stdin) == NULL) {
        return NULL;
    }

    input[strcspn(input, "\n")] = '\0';

    return input;
}