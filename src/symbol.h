
#ifndef __SYMBOL_H_
#define __SYMBOL_H_


// tokens and classes 标记和类（运算符放在最后且按优先级顺序排列）
enum {
    Num = 128, Fun, Sys, Glo, Loc, Id,
    Char, Else, Enum, If, Int, Return, Sizeof, While, 
    Assign, Cond, Lor, Lan, Or, Xor, And, Eq, Ne, Lt, Gt, Le, Ge, Shl, Shr, Add, Sub, Mul, Div, Mod, Inc, Dec, Brak
};

// operator codes (运算符代码)
enum {
    LEA, IMM, JMP, JSR, BZ, BNZ, ENT, ADJ, LEV, LI, LC, SI, SC, PSH,
    OR, XOR, AND, EQ, NE, LT, GT, LE, GE, SHL, SHR, ADD, SUB, MUL, DIV, MOD,
    OPEN, READ, CLOS, PRTF, MALC, FREE, MSET, MCMP, EXIT
};

// source types (源代码类型)
enum {
    CHAR, INT, PTR
};

// identitiers offsets (since we can't create an ident struct)
enum {
    Tk, Hash, Name, Class, Type, Val, HClass, Htype, HVal, Idsz
};

// 字符是否是数字
#define IS_DIGIT(c)       ((c) >= '0' && (c) <= '9') 
// 字符是否是大写字母
#define IS_UPPER_CHAR(c)  ((c) >= 'A' && (c) <= 'Z')
// 字符是否是小写字母
#define IS_LOWER_CHAR(c)  ((c) >= 'a' && (c) <= 'z')
// 字符是否是英文字母
#define IS_ALPHA(c)       (((c) >= 'a' && (c) <= 'z') || ((c) >= 'A' && (c) <= 'Z'))

#define and &&
#define or  ||
#define xor ^
#define bitand &
#define bitor |

#endif
