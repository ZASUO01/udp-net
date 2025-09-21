/**
 * @file addresses.h
 * @brief Definitions for socket adresses operations
 * @author ZASUO01
 */
#ifndef ADDRESSES_H
#define ADDRESSES_H

#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdint.h>

/**
 * @brief Initialize the socket addr with any internal address chosen by the system.
 * @param addr The socket addr.
 * @param port The port to be used in the socket addr.
 */
void init_any_addr_v4(struct sockaddr_in *addr, uint16_t port);

/**
 * @brief It looks for the local ip to be used to peers to  connect.
 * @return The local ip.
 */
char *get_public_lan_ip_v4();

#endif