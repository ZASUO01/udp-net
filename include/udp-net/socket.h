/**
 * @file socket.h
 * @brief Definitions the udp socket lifecycle functions
 * @author ZASUO01
 */
#ifndef SOCKET_H
#define SOCKET_H

#include "udp-net/packet.h"

#include <stdlib.h>
#include <arpa/inet.h>

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

/**
 * @brief Use poll to check if the socket has data to be received
 * @return 0 if it does have new data and -1 otherwise
 */
int socket_ready_to_receive(int fd, int ms);

/**
 * @brief Send a packet to an specified address.
 * @param fd The socket file descriptor.
 * @param pk The network packet.
 * @param pk_size The byte size of the packet
 * @param addr The destination address.
 * @return 0 if it succeeds and -1 otherwise
 */
int send_packet_to_v4(
    int fd, 
    UdpNetPacket *pk, 
    size_t pk_size,
    struct sockaddr_in *addr
);

/**
 * @brief Receive a packet from the socket and get the address.
 * @param fd The socket file descriptor.
 * @param pk The network packet.
 * @param addr The source address.
 * @return 0 if it succeeds and -1 otherwise
 */
int receive_packet_from_v4(int fd, UdpNetPacket *pk, struct sockaddr_in *addr);

#endif