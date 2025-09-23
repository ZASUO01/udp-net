#include "udp-net/parser.h"
#include "udp-net/logger.h"
#include "udp-net/defs.h"

#include <stdlib.h>

Params parse_args(int argc, char *argv[]){
    if(argc < 2){
        usage(argv[0]);
    }

    int mode = atoi(argv[1]);
    if(mode != SERVER_MODE && mode != CLIENT_MODE){
        usage(argv[0]);
    }

    Params p;
    p.mode = mode;

    return p;
}