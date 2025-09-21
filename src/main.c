#include <udp-net/packet.h>

int main(){
    UdpNetPacket pk;
    init_packet(&pk, 5, REQ_FLAG);
    add_uint32_to_packet(&pk, 23);
    add_string_to_packet(&pk, "ola mundo");
    add_int32_to_packet(&pk, -245);
    add_float_to_packet(&pk, 23.4);
    add_double_to_packet(&pk, 23.403);
    add_bool_to_packet(&pk, 0);
    add_string_to_packet(&pk, "muito louco");

    build_packet(&pk);

    print_packet(&pk);

    return 0;
}