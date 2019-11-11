
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <fcntl.h>
#include <stdint.h>

#include "config.h"
#include "util.h"
#include "type.h"
#include "symbol.h"

// 下移一个命令行参数指针
#define NEXT_CMD_ARGV {argc--; argv++;}
// 获取当前命令行参数
#define GET_ARGV (*argv)

char *p, *lp;  // current position in source code (源代码中的当前位置)
char *data;    // data/bss pointer (数据指针)

int *e, *le;   // current position in emitted code (发射代码中的当前位置)
int *id;       // currently parsed identifier (当前解析的标识符)
int *sym;      // symbol table (符号表)
int tk;        // current token (当前令牌)
int ival;      // current token value (当前令牌值)
int ty;        // current expression type (当前表达式类型)
int loc;       // local variable offset (局部变量偏移)
int line;      // current line number (当前行号)
int src;       // print source and assembly flag (是否打印源代码和汇编代码)
int debug;     // print executed instructions (是否打印执行指令)

int *pc, *sp, *bp, a, cycle; // vm regieters (虚拟机寄存器)

void varibles_malloc() {
    if (!(sym = malloc(POOL_SIZE))) {
        printf("could not malloc (%d) symbol area\n", POOL_SIZE);
        return MAIN_FUNC_RETURN_VAL;
    }
    if (!(le = e = malloc(POOL_SIZE))) {
        printf("could not malloc (%d) text area\n", POOL_SIZE);
        return MAIN_FUNC_RETURN_VAL;
    }
    if (!(data = malloc(POOL_SIZE))) {
        printf("could not malloc (%d) data area\n", POOL_SIZE);
        return MAIN_FUNC_RETURN_VAL;
    }
    if (!(sp = malloc(POOL_SIZE))) {
        printf("could not malloc (%d) stack area\n", POOL_SIZE);
        return MAIN_FUNC_RETURN_VAL;
    }
    memset(sym, 0, POOL_SIZE);
    memset(e, 0, POOL_SIZE);
    memset(data, 0, POOL_SIZE);
}

void varibles_free() {

}

void next() {
    char *pp;
    while (tk = *p) {
        ++p;
        if (tk == '\n') {
            if (src) {
                printf("%d: %.*s", line, p - lp, lp);
                lp = p;
                while (le < e) {
                    printf("%8.4s", &"LEA ,IMM ,JMP ,JSR ,BZ  ,BNZ ,ENT ,ADJ ,LEV ,LI  ,LC  ,SI  ,SC  ,PSH ,"
                           "OR  ,XOR ,AND ,EQ  ,NE  ,LT  ,GT  ,LE  ,GE  ,SHL ,SHR ,ADD ,SUB ,MUL ,DIV ,MOD ,"
                           "OPEN,READ,CLOS,PRTF,MALC,FREE,MSET,MCMP,EXIT,"[*++le * 5]);
                    if (*le <= ADJ) 
                        printf(" %d\n", *++le); 
                    else 
                        printf("\n");
                }
            }
            ++line;
        }
        else if (tk == '#') {
            while (*p != 0 && *p != '\0')
                ++p;
        }
        else if (IS_ALPHA(tk) || tk == '_') {
            pp = p - 1;
            while (IS_ALPHA(*p) || IS_DIGIT(*p) || (*p) == '_') {
                tk = tk * 147 + *p++;
            }
            tk = (tk << 6) + (p - pp);
            id = sym;
            while (id[Tk]) {
                if (tk == id[Hash] && !memcmp((char *)id[Name], pp, p - pp)) {
                    tk = id[Tk];
                    return;
                }
                id = id + Idsz;
            }
            id[Name] = (int)pp;
            id[Hash] = tk;
            tk = id[tk] = Id;
            return;
        }
        else if (IS_DIGIT(tk)) {
            if (ival = tk - '0') {
                while (IS_DIGIT(*p)) {
                    ival = ival * 10 + *p++ - '0';
                } 
            }
            else if (*p == 'x' or *p == 'X') {
                while ( (tk = *++p) && IS_DIGIT_HEX(tk)) {
                    ival = ival * 16 + (tk & 15) + (tk >= 'A' ? 9 : 0);
                }         
            }
            else {
                while (IS_DIGIT_OCTAL(*p)) {
                    ival = ival * 8 + *p++ - '0';
                }    
            }
            tk = Num;
            return;
        }
        else if (tk == '/') {
            if (*p == '/') {
                ++p;
                while (*p != 0 && *p != '\n') {
                    ++p;
                }  
            }
            else {
                tk = Div;
                return;
            }
        }
        else if (tk == '\'' || tk ==  '"') {
            pp = data;
            while (*p != 0 && *p != tk) {
                // 遇到了转义字符
                if ((ival = *p++) == '\\') {
                    if ((ival = *p++) == 'n') {
                        ival = '\n';
                    }
                }
                if (tk == '"')
                    *data++ = ival;
            }     
            ++p;
            if (tk == '"') 
                ival = (int)pp;
            else 
                tk = Num;
            return;
        }
        else if (tk == '=') {
            if (p == '=') {
                ++p;
                tk = Eq;
            }
            else 
                tk = Assign;
            return;
        }
        else if (tk == '+') {
            if (*p == '+') {
                ++p;
                tk = Inc;
            }
            else
                tk = Add;
            return;
        }
        else if (tk == '-') {
            if (*p == '-') {
                ++p;
                tk = Dec
            }
            else
                tk = Sub;
            return;
        }
        else if (tk == '!') {
            if (*p == '=') {
                ++p;
                tk = Ne;
            }
            return;
        }
        else if (tk == '<') {
            if (*p == '=') {
                ++p;
                tk = Le;
            }
            else if (*p == '<') {
                ++p;
                tk = Shl;
            }
            else
                tk = Lt;
            return;
        }
        else if (tk == '>') {
            if (*p == '=') {
                ++p;
                tk = Ge;
            }
            else if (*p == '>') {
                ++p;
                tk = Shr;
            }
            else 
                tk = Gt;
            return;
        }
        else if (tk == '|') {
            if (*p == '|') {
                ++p;
                tk = Lor;
            }
            else 
                tk = Or;
            return;
        }
        else if (tk == '&') {
            if (*p == '&') {
                ++p;
                tk = Lan;
            }
            else 
                tk = And;
            return;
        }
        else if (tk = '^') {
            tk = Xor;
            return;
        }
        else if (tk = '%') {
            tk = Mod;
            return;
        }
        else if (tk = '*') {
            tk = Mod;
            return;
        }
        else if (tk == '*') {
            tk = Mul;
            return;
        }
        else of (tk == '?') {
            tk = Cond;
            return;
        }
        else if (tk == '~' || tk == '{' || tk == '}' || tk == '(' || tk == ')' || tk == '[' || tk == ']' || tk == ',' || tk == ':')
            return;
    }
}

void expr() {

}

void stmt() {

}

int main(int argc, char **argv) { 
    int fd, bt, ty, *idmain;
    int i, *t;  
    NEXT_CMD_ARGV;
    if (argc > 0 && GET_ARGV[0] == '-' && GET_ARGV[0] == 's') {
        src = TRUE;
        NEXT_CMD_ARGV;
    }
    if (argc > 0 && GET_ARGV[0] == '-' && GET_ARGV[1] == 'd') {
        debug = TRUE;
        NEXT_CMD_ARGV;
    }
    if (argc < 1) {
        printf("Hello dugu complier! The version is %s\n", DUGU_VERSION);
    }
    if ( (fd = open(GET_ARGV, 0)) < 0) {
        printf("cound not open (%s)\n", GET_ARGV);
        return MAIN_FUNC_RETURN_VAL;
    }
    varibles_malloc();
    p = "char else enum if int return sizeof while "
      "open read close printf malloc free memset memcmp exit void main";
    i = CHAR;
    while (i <= While) {
        // add keywords to symbol table (向字符表添加关键字)
        next();
        id[Tk] = i++;
    }
    i = OPEN;
    while (i <= EXIT) {
        // add library to symbol table (向字符表添加库)
        next();
        id[Class] = Sys;
        id[Type] = Int;
        id[Val] = i++;
    }
    next(); id[Tk] = Char;
    next(); idmain = id;

    varibles_free();
    return MAIN_FUNC_RETURN_VAL;
}
