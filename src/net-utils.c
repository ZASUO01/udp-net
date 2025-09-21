#include "udp-net/net-utils.h"

#include <string.h>

uint16_t get_net_checksum(const void *data, size_t data_size){
    const uint8_t *buf = (const uint8_t *)data;
    uint32_t sum = 0;
   
    for (size_t i = 0; i + 1 < data_size; i += 2) {
        uint16_t word;
        memcpy(&word, buf + i, sizeof(uint16_t));
        sum += word;
    }

    if(data_size % 2 != 0){
        sum += (uint16_t)(buf[data_size - 1] << 8);
    }

    while (sum >> 16) {
        sum = (sum & 0xFFFF) + (sum >> 16);
    }

    return (uint16_t)(~sum);
}