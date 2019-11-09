
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <fcntl.h>
#include <stdint.h>

#include "config.h"
#include "type.h"
#include "symbol.h"

#define NEXT_CMD_ARGV {argc--; argv++;}
#define GET_ARGV (*argv)

cmd_para_t para = {0};

void next() {

}

void expr() {

}

void stmt() {

}

int main(int argc, char **argv) { 
    NEXT_CMD_ARGV;
    if (argc > 0 && GET_ARGV[0] == '-' && GET_ARGV[0] == 's') {
        para.src = 1;
        NEXT_CMD_ARGV;
    }
    if (argc > 0 && GET_ARGV[0] == '-' && GET_ARGV[1] == 'd') {
        para.debug = 1;
        NEXT_CMD_ARGV;
    }
    if (argc < 1) {
        printf("Hello dugu complier! The version is %s\n", DUGU_VERSION);
    }
    printf("%d\n", argc);
    return -1;
}
