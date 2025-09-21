#include "udp-net/addresses.h"

void init_any_addr_v4(struct sockaddr_in *addr, uint16_t port){
    addr->sin_family = AF_INET;
    addr->sin_port = htons(port);
    addr->sin_addr.s_addr = INADDR_ANY;
}
