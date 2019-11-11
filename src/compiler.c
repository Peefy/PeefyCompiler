
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <fcntl.h>
#include <stdint.h>

#include "config.h"
#include "type.h"
#include "symbol.h"

// 下移一个命令行参数指针
#define NEXT_CMD_ARGV {argc--; argv++;}
// 获取当前命令行参数
#define GET_ARGV (*argv)

char *p, *lp;  // current position in source code (源代码中的当前位置)
char *data;    // data/bss pointer (数据指针)

int *e, *le,   // current position in emitted code (发射代码中的当前位置)
    *id,       // currently parsed identifier (当前解析的标识符)
    *sym,      // symbol table (符号表)
    tk,        // current token (当前令牌)
    ival,      // current token value (当前令牌值)
    ty,        // current expression type (当前表达式类型)
    loc,       // local variable offset (局部变量偏移)
    line,      // current line number (当前行号)
    src,       // print source and assembly flag (是否打印源代码和汇编代码)
    debug;     // print executed instructions (是否打印执行指令)


void next() {

}

void expr() {

}

void stmt() {

}

int main(int argc, char **argv) { 
    int fd, bt, ty, poolsz, *idmain;
    int *pc, *sp, *bp, a, cycle; // vm regieters (虚拟机寄存器)
    int i, *t;  
    NEXT_CMD_ARGV;
    if (argc > 0 && GET_ARGV[0] == '-' && GET_ARGV[0] == 's') {
        src = 1;
        NEXT_CMD_ARGV;
    }
    if (argc > 0 && GET_ARGV[0] == '-' && GET_ARGV[1] == 'd') {
        debug = 1;
        NEXT_CMD_ARGV;
    }
    if (argc < 1) {
        printf("Hello dugu complier! The version is %s\n", DUGU_VERSION);
    }
    if ( (fd = open(GET_ARGV, 0)) < 0) {
        printf("cound not open (%s)\n", GET_ARGV);
        return -1;
    }
    poolsz = 256 * 1024;
    if (!(sym = malloc(poolsz)))
    return -1;
}
