
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <fcntl.h>
#include <stdint.h>

#include "config.h"
#include "type.h"
#include "symbol.h"

cmd_para_t para = {0};

void next() {

}

void expr() {

}

void stmt() {

}

int main(int argc, char **argv) { 
    argc--; argv++;
    if (argc > 0 && **argv == '-' && (*argv)[1] == 's') {
        para.src = 1;
        --argc; ++argv;
    }
    if (argc > 0 && **argv == '-' && (*argv)[1] == 'd') {
        para.debug = 1;
        --argc; ++argv;
    }
    if (argc < 1) {
        printf("Hello dugu complier! The version is %s\n", DUGU_VERSION);
    }
    printf("%d\n", argc);
    return -1;
}
