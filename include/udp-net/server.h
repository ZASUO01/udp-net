/**
 * @file server.h
 * @brief Definitions the server main operations
 * @author ZASUO01
 */
#ifndef SERVER_H
#define SERVER_H

#include <udp-net/defs.h>

/**
 * @brief Initialize the server struct with initial values.
 * @param s Pointer to the server struct.
 */
void init_server(Server *s);

/**
 * @brief Create an UDP socket and set to the server.
 * @param s Pointer to the server struct.
 */
void set_server_socket(Server *s);

/**
 * @brief Bind the server socket to an internal ip addr and port
 * @param s Pointer to the server struct.
 */
void bind_server_socket(Server *s);

/** @brief Show the local addresses to the peers to connect. */
void print_server_addrs();

/**
 * @brief Stop the server operation and clean variables
 * @param s Pointer to the server struct.
 */
void close_server(Server *s);

#endif