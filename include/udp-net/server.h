/**
 * @file server.h
 * @brief Definitions the server main operations
 * @author ZASUO01
 */
#ifndef SERVER_H
#define SERVER_H

#include <pthread.h>
#include <arpa/inet.h>

typedef struct {
    int running;
    int sock_fd;

    pthread_t receive_t;
    pthread_mutex_t server_mutex;
    
} Server;


typedef struct {
    struct sockaddr_in peer_addr_v4;
} Peer;


/** @brief Global server variable */
extern Server server;

/** @brief Initialize the server struct with initial values. */
void init_server();

/** @brief Create an UDP socket and set to the server. */
void set_server_socket();

/** @brief Bind the server socket to an internal ip addr and port */
void bind_server_socket();

/** @brief Set the server to running */
void start_sever();

/** @brief Show the local addresses to the peers to connect. */
void print_server_addrs();

/** @brief Read terminal inputs to control the server state  */
void read_inputs();

/** @brief Init server thread operations */
void init_server_threads();

/** @brief Wait for all the initialed threads to finish */
void join_server_threads();

/** @brief Stop the server operation and clean variables */
void close_server();

#endif