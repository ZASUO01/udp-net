/**
 * @file defs.h
 * @brief Definitions constants and structs used by the program
 * @author ZASUO01
 */
#ifndef DEFS_H
#define DEFS_H

#include <stdint.h>

// PACKET
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

//SERVER
typedef struct {
    int running;
    int sock_fd;
} Server;

#endif