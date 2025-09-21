/**
 * @file packet.h
 * @brief Definitions for packets lifecycle functions
 * @author ZASUO01
 */
#ifndef PACKET_H
#define PACKET_H

#include "udp-net/defs.h"

/**
 * @brief Initialize the packet fields.
 * @param p A pointer to the packet.
 * @param id The packet desired identifier.
 * @param flag The packet desired flag.
 */
void init_packet(UdpNetPacket *p, uint8_t id, uint8_t flag);

/**
 * @brief Make the packet ready to be sent to the network.
 * @param p A pointer to the packet.
 */
void build_packet(UdpNetPacket *p);

/**
 * @brief Verify if received packet is valid or not. Packets either not built or with byte errors will fail this verification. 
 * @param p A pointer to the packet.
 */
int is_valid_packet(UdpNetPacket *p);

#endif