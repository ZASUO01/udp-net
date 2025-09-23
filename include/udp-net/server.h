/**
 * @file server.h
 * @brief Definitions the server main operations
 * @author ZASUO01
 */
#ifndef SERVER_H
#define SERVER_H

#include <udp-net/defs.h>

/** @brief Global server variable */
extern Server server;

/** @brief Initialize the server struct with initial values. */
void init_server();

/** @brief Create an UDP socket and set to the server. */
void set_server_socket();

/** @brief Bind the server socket to an internal ip addr and port */
void bind_server_socket();

/** @brief Show the local addresses to the peers to connect. */
void print_server_addrs();

/** @brief Stop the server operation and clean variables */
void close_server();

/** @brief Read terminal inputs to control the server state  */
void read_inputs();

/** @brief Thread function to receive network data */
void *receive_data(void *arg);

#endif