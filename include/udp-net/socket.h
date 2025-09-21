/**
 * @file socket.h
 * @brief Definitions the udp socket lifecycle functions
 * @author ZASUO01
 */
#ifndef SOCKET_H
#define SOCKET_H

/**
 * @brief Create an UDP socket.
 * @return The socket file descriptor.
 */
int create_socket_v4();

/** 
 * @brief Bind the UDP socket to any internal ip. 
 * @param fd Socket file descriptor. 
 */
void bind_socket_to_any_v4(int fd);

#endif