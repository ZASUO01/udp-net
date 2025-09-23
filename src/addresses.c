#include "udp-net/addresses.h"

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

static char *get_public_ip_by_dns_v4(const char *dns_ip);

void init_any_addr_v4(struct sockaddr_in *addr, uint16_t port){
    addr->sin_family = AF_INET;
    addr->sin_port = htons(port);
    addr->sin_addr.s_addr = INADDR_ANY;
}


char *get_public_lan_ip_v4(){
    static const char *dns_ips[] = {
        "8.8.8.8",
        "1.1.1.1",
        "9.9.9.9",
        "208.67.222.222"
    };
    int size = 4;

    for(int i = 0; i < size; i++){
        char *ip = get_public_ip_by_dns_v4(dns_ips[i]);
        if(ip != NULL){
            return ip;
        }
    }

    return NULL;
}

int parse_addr_v4(const char *ip, struct sockaddr_in *addr4, uint16_t port){
    struct in_addr addr;
    if(inet_pton(AF_INET, ip, &addr) != 1) {
        return -1;
    }

    addr4->sin_addr = addr;
    addr4->sin_port = htons(port);
    addr4->sin_family = AF_INET;

    return 0;
}


static char *get_public_ip_by_dns_v4(const char *dns_ip){
    int sock_fd = socket(AF_INET, SOCK_DGRAM, 0);
    if(sock_fd < 0){
        return NULL;
    }

    struct sockaddr_in dns_addr;
    dns_addr.sin_family = AF_INET;
    dns_addr.sin_port = htons(53);
    inet_pton(AF_INET, dns_ip, &dns_addr.sin_addr);

    if (connect(sock_fd, (struct sockaddr*)&dns_addr, sizeof(dns_addr)) < 0) {
        close(sock_fd);
        return NULL;
    }

    struct sockaddr_in local_addr;
    socklen_t addr_len = sizeof(local_addr);
    if (getsockname(sock_fd, (struct sockaddr*)&local_addr, &addr_len) < 0) {
        close(sock_fd);
        return NULL;
    }

    char *ip = malloc(INET_ADDRSTRLEN);
    if (inet_ntop(AF_INET, &local_addr.sin_addr, ip, INET_ADDRSTRLEN) == NULL) {
        close(sock_fd);
        return NULL;
    }

    close(sock_fd);
    return ip;
}

