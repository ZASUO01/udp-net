/**
 * @file client.h
 * @brief Definitions the client main operations
 * @author ZASUO01
 */
#ifndef CLIENT_H
#define CLIENT_H

#include <stdlib.h>
#include <arpa/inet.h>
#include <stdint.h>

typedef enum{
    CLOSED = 0,
    REQ_SENT,
    ACC_RECEIVED,
    ESTABLISHED,
} ClientState;

typedef struct {
    int sock_fd;
    struct sockaddr_in server_addr;
    ClientState state;
    uint8_t current_id;
    uint8_t received_ack;
    int total_attempts;
} Client;


/** @brief Global client variable */
extern Client client;

/** @brief Initialize the client struct with initial values. */
void init_client();

/** @brief Create an UDP socket and set to the client. */
void set_client_socket();

/** 
 * @brief Read inputs from terminal and try to parse an ip or Quit the program 
 * @param buff The string to receive the ip.
 * @param buff_size The string size.
 */
void read_server_ip_from_terminal(char *buff, size_t buff_size);

/** @brief Register the target server addr */
void add_server_addr_to_client(const char *ip);

/** @brief UDP handshake protocol with the server */
void start_handshake();

/** @brief Stop the client operation and clean variables */
void close_client();



#endif