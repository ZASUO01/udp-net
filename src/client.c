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

static int send_request();
static int wait_for_acc();
static int send_ack();

void init_client(){
    client.sock_fd = -1;
    client.state = CLOSED;
    client.current_id = 0;
    client.received_ack = 0;
    client.total_attempts = 0;
    
    LOG_MSG(LOG_INFO, "client initialized");
}

void set_client_socket(){
    if(client.state == CLOSED){
        client.sock_fd = create_socket_v4();

        LOG_MSG(LOG_INFO, "client socket created");
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
    if(client.state == CLOSED){
        struct sockaddr_in server_addr;

        if(parse_addr_v4(ip, &server_addr, APP_PORT) != 0){
            log_exit("invalid server addr");
        }

        client.server_addr = server_addr;

        LOG_MSG(LOG_INFO, "server address added");
    }
}

void start_handshake(){
    if(client.state == CLOSED){
        if(send_request() != 0){
            log_exit("send request failure");
        }

        if(wait_for_acc() != 0){
            log_exit("server accept failure");
        }

        if(send_ack() != 0){
            log_exit("send ack failure");
            }
    
        LOG_MSG(LOG_INFO, "client handshake done");
    }
}

void close_client(){
    if(client.state == ESTABLISHED){
        client.state = CLOSED;
    
        if(close(client.sock_fd) < 0){
            sys_log_exit("socket closure failure");
        }
    
        LOG_MSG(LOG_INFO, "client closed");
    }
}


static int send_request(){
    if(client.state == CLOSED || client.state == REQ_SENT){
        LOG_MSG(LOG_DEBUG, "send_request() start");

        UdpNetPacket req;
        init_packet(&req, client.current_id, REQ_FLAG);
        build_packet(&req);
        
        size_t req_size = PACKET_HEADER_BYTES;

        if(send_packet_to_v4(client.sock_fd, &req, req_size, &client.server_addr) != 0){
            LOG_MSG(LOG_DEBUG, "send_request() failed");
            return -1;
        }

        client.state = REQ_SENT;

        LOG_MSG(LOG_DEBUG, "send_request() done");
        return 0;
    }

    LOG_MSG(LOG_DEBUG, "send_request() invalid call");
    return -1;
}

static int wait_for_acc(){
    if(client.state == REQ_SENT){
        LOG_MSG(LOG_DEBUG, "wait_for_acc() start");

        UdpNetPacket res;

        while(client.total_attempts < MAX_ATTEMPTS){
            client.total_attempts++;

            if(socket_ready_to_receive(client.sock_fd, RECV_TIMEOUT_IN_SECS * 1000) != 0){
                LOG_MSG(LOG_DEBUG, "wait_for_acc() retry");
                
                send_request();
                continue;
            }

            if(receive_packet_from_v4(client.sock_fd, &res, &client.server_addr) != 0){
                LOG_MSG(LOG_DEBUG, "wait_for_acc() retry");
                continue;
            }

            if(is_valid_packet(&res) != 0){
                LOG_MSG(LOG_DEBUG, "wait_for_acc() retry");
                continue;
            }

            if(res.flag == ACC_FLAG){
                if(res.id  == client.received_ack + 1){
                    client.received_ack = res.id;
                    client.current_id++;
                    client.state = ACC_RECEIVED;

                    LOG_MSG(LOG_DEBUG, "wait_for_acc() received");
                    return 0;
                }
                LOG_MSG(LOG_DEBUG, "wait_for_acc() retry");
            }
        }

        LOG_MSG(LOG_DEBUG, "wait_for_acc() failed");
        return -1;
    }

    LOG_MSG(LOG_DEBUG, "wait_for_acc() invalid call");
    return -1;
}

static int send_ack(){
    if(client.state == ACC_RECEIVED){
        LOG_MSG(LOG_DEBUG, "send_ack() start");

        UdpNetPacket ack;
        init_packet(&ack, client.current_id, ACK_FLAG);
        build_packet(&ack);
        
        size_t ack_size = PACKET_HEADER_BYTES;

        if(send_packet_to_v4(client.sock_fd, &ack, ack_size, &client.server_addr) != 0){
            LOG_MSG(LOG_DEBUG, "send_ack() failed");
            return -1;
        }

        client.state = ESTABLISHED;

        LOG_MSG(LOG_DEBUG, "send_ack() done");
        return 0;
    }

    LOG_MSG(LOG_DEBUG, "send_ack() invalid call");
    return -1;
}