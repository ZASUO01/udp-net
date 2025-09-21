#include "udp-net/packet.h"
#include "udp-net/net-utils.h"

#include <string.h>
#include <arpa/inet.h>

void init_packet(UdpNetPacket *p, uint8_t id, uint8_t flag){
    p->sync_1 = PACKET_SYNC_BYTES;
    p->sync_2 = PACKET_SYNC_BYTES;
    p->ready = 0;
    p->id = id;
    p->flag = flag;
    p->length = 0;
    p->checksum = 0;
    memset(p->data, 0, MAX_PACKET_DATA_BYTES);
}

void build_packet(UdpNetPacket *p){
    if(p->ready == 0){
        p->ready = 1;
        p->sync_1 = htonl(PACKET_SYNC_BYTES);
        p->sync_2 = htonl(PACKET_SYNC_BYTES);

        uint16_t _length = p->length;
        p->length = htons(p->length);
        
        size_t packet_size = PACKET_HEADER_BYTES + _length; 
        p->checksum = get_net_checksum(p, packet_size);
    }
}

int is_valid_packet(UdpNetPacket *p){
    if(p->ready == 0){
        return -1;
    }
    
    if(p->sync_1 != htonl(PACKET_SYNC_BYTES) || 
       p->sync_2 != htonl(PACKET_SYNC_BYTES)) {
        return -1;
    }

    uint16_t _length = ntohs(p->length);
    if(_length > MAX_PACKET_DATA_BYTES){
        return -1;
    }

    UdpNetPacket temp;
    memcpy(&temp, p, sizeof(UdpNetPacket));
    temp.checksum = 0;

    size_t packet_size = PACKET_HEADER_BYTES + _length;
    uint16_t calculated_checksum = get_net_checksum(&temp, packet_size);

    if(calculated_checksum != p->checksum){
        return -1;
    }

    return 0;
}