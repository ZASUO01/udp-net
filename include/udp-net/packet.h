/**
 * @file packet.h
 * @brief Definitions for packets lifecycle functions
 * @author ZASUO01
 */
#ifndef PACKET_H
#define PACKET_H

#include <stdint.h>

#define PACKET_HEADER_BYTES 15
#define PACKET_SYNC_BYTES 0x554E4554
#define MAX_PACKET_DATA_BYTES 1024
#define MAX_PACKET_DATA_STRING_BYTES 256

#define REQ_FLAG 0x01
#define ACC_FLAG 0x02
#define ACK_FLAG 0x03
#define DATA_FLAG 0x04
#define END_FLAG 0x05
#define RST_FLAG 0x06

typedef enum {
    UINT32_TYPE = 0,
    INT32_TYPE,
    FLOAT_TYPE,
    DOUBLE_TYPE,
    BOOL_TYPE,
    STRING_TYPE
} DataType;

typedef struct {
    DataType type;
    union {
        uint32_t uint32_value;
        int32_t  int32_value;
        float float_value;
        double double_value;
        uint8_t bool_value;
        char string_value[MAX_PACKET_DATA_STRING_BYTES];
    } value;
} UdpNetPacketDataField;

#pragma pack(1)
typedef struct {
    uint32_t sync_1;
    uint32_t sync_2;
    uint8_t ready;
    uint8_t id;
    uint8_t flag;
    uint16_t length;
    uint16_t checksum;
    char data[MAX_PACKET_DATA_BYTES];
} UdpNetPacket;
#pragma pack(0)

/**
 * @brief Initialize the packet fields.
 * @param p A pointer to the packet.
 * @param id The packet desired identifier.
 * @param flag The packet desired flag.
 */
void init_packet(UdpNetPacket *p, uint8_t id, uint8_t flag);

/**
 * @brief Adds a 4 bytes unsigned int field to the packet
 * @param p A pointer to the packet.
 * @param value The 4 bytes unsigned int value.
 */
void add_uint32_to_packet(UdpNetPacket *p, uint32_t value);

/**
 * @brief Adds a 4 bytes int field to the packet
 * @param p A pointer to the packet.
 * @param value The 4 bytes int value.
 */
void add_int32_to_packet(UdpNetPacket *p, int32_t value);

/**
 * @brief Adds a float field to the packet
 * @param p A pointer to the packet.
 * @param value The float value.
 */
void add_float_to_packet(UdpNetPacket *p, float value);

/**
 * @brief Adds a double field to the packet
 * @param p A pointer to the packet.
 * @param value The double value.
 */
void add_double_to_packet(UdpNetPacket *p, double value);

/**
 * @brief Adds a 1 byte unsigned int boolean field to the packet
 * @param p A pointer to the packet.
 * @param value The 1 byte unsigned int boolean value.
 */
void add_bool_to_packet(UdpNetPacket *p, uint8_t value);

/**
 * @brief Adds a string field to the packet
 * @param p A pointer to the packet.
 * @param value The string value.
 */
void add_string_to_packet(UdpNetPacket *p, const char *value);

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

/**
 * @brief It prints the content of a built packet.
 * @param p A pointer to the packet.
 */
void print_packet(UdpNetPacket *p);

#endif