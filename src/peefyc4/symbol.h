
#ifndef __SYMBOL_H__
#define __SYMBOL_H__


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

#endif
