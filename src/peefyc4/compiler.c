
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

#define int long long

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

int *pc, *sp, *bp, a, cycle; // vm regieters (虚拟机寄存器) pc 程序计数器  sp 堆栈指针

void varibles_malloc() {
    if (!(sym = malloc(POOL_SIZE))) {
        printf("could not malloc (%d) symbol area\n", POOL_SIZE);
        return;
    }
    if (!(le = e = malloc(POOL_SIZE))) {
        printf("could not malloc (%d) text area\n", POOL_SIZE);
        return;
    }
    if (!(data = malloc(POOL_SIZE))) {
        printf("could not malloc (%d) data area\n", POOL_SIZE);
        return;
    }
    if (!(sp = malloc(POOL_SIZE))) {
        printf("could not malloc (%d) stack area\n", POOL_SIZE);
        return;
    }
    memset(sym, 0, POOL_SIZE);
    memset(e, 0, POOL_SIZE);
    memset(data, 0, POOL_SIZE);
}

void varibles_free() {
    free(sym);
    free(le);
    free(e);
    free(data);
    free(sp);
}

// 词法分析器，下一个记号token
void next()
{
  char *pp;

  while (tk = *p)
  {
    ++p;
    if (tk == '\n')
    {
      if (src)
      {
        printf("%d: %.*s", line, p - lp, lp);
        lp = p;
        while (le < e)
        {
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
    else if (tk == '#')
    {
      while (*p != 0 && *p != '\n')
        ++p;
    }
    else if ((tk >= 'a' && tk <= 'z') || (tk >= 'A' && tk <= 'Z') || tk == '_')
    {
      pp = p - 1;
      while ((*p >= 'a' && *p <= 'z') || (*p >= 'A' && *p <= 'Z') || (*p >= '0' && *p <= '9') || *p == '_')
        tk = tk * 147 + *p++;
      tk = (tk << 6) + (p - pp);
      id = sym;
      while (id[Tk])
      {
        if (tk == id[Hash] && !memcmp((char *)id[Name], pp, p - pp))
        {
          tk = id[Tk];
          return;
        }
        id = id + Idsz;
      }
      id[Name] = (int)pp;
      id[Hash] = tk;
      tk = id[Tk] = Id;
      return;
    }
    else if (tk >= '0' && tk <= '9')
    {
      if (ival = tk - '0')
      {
        while (*p >= '0' && *p <= '9')
          ival = ival * 10 + *p++ - '0';
      }
      else if (*p == 'x' || *p == 'X')
      {
        while ((tk = *++p) && ((tk >= '0' && tk <= '9') || (tk >= 'a' && tk <= 'f') || (tk >= 'A' && tk <= 'F')))
          ival = ival * 16 + (tk & 15) + (tk >= 'A' ? 9 : 0);
      }
      else
      {
        while (*p >= '0' && *p <= '7')
          ival = ival * 8 + *p++ - '0';
      }
      tk = Num;
      return;
    }
    else if (tk == '/')
    {
      if (*p == '/')
      {
        ++p;
        while (*p != 0 && *p != '\n')
          ++p;
      }
      else
      {
        tk = Div;
        return;
      }
    }
    else if (tk == '\'' || tk == '"')
    {
      pp = data;
      while (*p != 0 && *p != tk)
      {
        if ((ival = *p++) == '\\')
        {
          if ((ival = *p++) == 'n')
            ival = '\n';
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
    else if (tk == '=')
    {
      if (*p == '=')
      {
        ++p;
        tk = Eq;
      }
      else
        tk = Assign;
      return;
    }
    else if (tk == '+')
    {
      if (*p == '+')
      {
        ++p;
        tk = Inc;
      }
      else
        tk = Add;
      return;
    }
    else if (tk == '-')
    {
      if (*p == '-')
      {
        ++p;
        tk = Dec;
      }
      else
        tk = Sub;
      return;
    }
    else if (tk == '!')
    {
      if (*p == '=')
      {
        ++p;
        tk = Ne;
      }
      return;
    }
    else if (tk == '<')
    {
      if (*p == '=')
      {
        ++p;
        tk = Le;
      }
      else if (*p == '<')
      {
        ++p;
        tk = Shl;
      }
      else
        tk = Lt;
      return;
    }
    else if (tk == '>')
    {
      if (*p == '=')
      {
        ++p;
        tk = Ge;
      }
      else if (*p == '>')
      {
        ++p;
        tk = Shr;
      }
      else
        tk = Gt;
      return;
    }
    else if (tk == '|')
    {
      if (*p == '|')
      {
        ++p;
        tk = Lor;
      }
      else
        tk = Or;
      return;
    }
    else if (tk == '&')
    {
      if (*p == '&')
      {
        ++p;
        tk = Lan;
      }
      else
        tk = And;
      return;
    }
    else if (tk == '^')
    {
      tk = Xor;
      return;
    }
    else if (tk == '%')
    {
      tk = Mod;
      return;
    }
    else if (tk == '*')
    {
      tk = Mul;
      return;
    }
    else if (tk == '[')
    {
      tk = Brak;
      return;
    }
    else if (tk == '?')
    {
      tk = Cond;
      return;
    }
    else if (tk == '~' || tk == ';' || tk == '{' || tk == '}' || tk == '(' || tk == ')' || tk == ']' || tk == ',' || tk == ':')
      return;
  }
}

// 表达式
void expr(int lev)
{
  int t, *d;

  if (!tk)
  {
    printf("%d: unexpected eof in expression\n", line);
    exit(-1);
  }
  else if (tk == Num)
  {
    *++e = IMM;
    *++e = ival;
    next();
    ty = INT;
  }
  else if (tk == '"')
  {
    *++e = IMM;
    *++e = ival;
    next();
    while (tk == '"')
      next();
    data = (char *)((int)data + sizeof(int) & -sizeof(int));
    ty = PTR;
  }
  else if (tk == Sizeof)
  {
    next();
    if (tk == '(')
      next();
    else
    {
      printf("%d: open paren expected in sizeof\n", line);
      exit(-1);
    }
    ty = INT;
    if (tk == Int)
      next();
    else if (tk == Char)
    {
      next();
      ty = CHAR;
    }
    while (tk == Mul)
    {
      next();
      ty = ty + PTR;
    }
    if (tk == ')')
      next();
    else
    {
      printf("%d: close paren expected in sizeof\n", line);
      exit(-1);
    }
    *++e = IMM;
    *++e = (ty == CHAR) ? sizeof(char) : sizeof(int);
    ty = INT;
  }
  else if (tk == Id)
  {
    d = id;
    next();
    if (tk == '(')
    {
      next();
      t = 0;
      while (tk != ')')
      {
        expr(Assign);
        *++e = PSH;
        ++t;
        if (tk == ',')
          next();
      }
      next();
      if (d[Class] == Sys)
        *++e = d[Val];
      else if (d[Class] == Fun)
      {
        *++e = JSR;
        *++e = d[Val];
      }
      else
      {
        printf("%d: bad function call\n", line);
        exit(-1);
      }
      if (t)
      {
        *++e = ADJ;
        *++e = t;
      }
      ty = d[Type];
    }
    else if (d[Class] == Num)
    {
      *++e = IMM;
      *++e = d[Val];
      ty = INT;
    }
    else
    {
      if (d[Class] == Loc)
      {
        *++e = LEA;
        *++e = loc - d[Val];
      }
      else if (d[Class] == Glo)
      {
        *++e = IMM;
        *++e = d[Val];
      }
      else
      {
        printf("%d: undefined variable\n", line);
        exit(-1);
      }
      *++e = ((ty = d[Type]) == CHAR) ? LC : LI;
    }
  }
  else if (tk == '(')
  {
    next();
    if (tk == Int || tk == Char)
    {
      t = (tk == Int) ? INT : CHAR;
      next();
      while (tk == Mul)
      {
        next();
        t = t + PTR;
      }
      if (tk == ')')
        next();
      else
      {
        printf("%d: bad cast\n", line);
        exit(-1);
      }
      expr(Inc);
      ty = t;
    }
    else
    {
      expr(Assign);
      if (tk == ')')
        next();
      else
      {
        printf("%d: close paren expected\n", line);
        exit(-1);
      }
    }
  }
  else if (tk == Mul)
  {
    next();
    expr(Inc);
    if (ty > INT)
      ty = ty - PTR;
    else
    {
      printf("%d: bad dereference\n", line);
      exit(-1);
    }
    *++e = (ty == CHAR) ? LC : LI;
  }
  else if (tk == And)
  {
    next();
    expr(Inc);
    if (*e == LC || *e == LI)
      --e;
    else
    {
      printf("%d: bad address-of\n", line);
      exit(-1);
    }
    ty = ty + PTR;
  }
  else if (tk == '!')
  {
    next();
    expr(Inc);
    *++e = PSH;
    *++e = IMM;
    *++e = 0;
    *++e = EQ;
    ty = INT;
  }
  else if (tk == '~')
  {
    next();
    expr(Inc);
    *++e = PSH;
    *++e = IMM;
    *++e = -1;
    *++e = XOR;
    ty = INT;
  }
  else if (tk == Add)
  {
    next();
    expr(Inc);
    ty = INT;
  }
  else if (tk == Sub)
  {
    next();
    *++e = IMM;
    if (tk == Num)
    {
      *++e = -ival;
      next();
    }
    else
    {
      *++e = -1;
      *++e = PSH;
      expr(Inc);
      *++e = MUL;
    }
    ty = INT;
  }
  else if (tk == Inc || tk == Dec)
  {
    t = tk;
    next();
    expr(Inc);
    if (*e == LC)
    {
      *e = PSH;
      *++e = LC;
    }
    else if (*e == LI)
    {
      *e = PSH;
      *++e = LI;
    }
    else
    {
      printf("%d: bad lvalue in pre-increment\n", line);
      exit(-1);
    }
    *++e = PSH;
    *++e = IMM;
    *++e = (ty > PTR) ? sizeof(int) : sizeof(char);
    *++e = (t == Inc) ? ADD : SUB;
    *++e = (ty == CHAR) ? SC : SI;
  }
  else
  {
    printf("%d: bad expression\n", line);
    exit(-1);
  }

  while (tk >= lev)
  { // "precedence climbing" or "Top Down Operator Precedence" method
    t = ty;
    if (tk == Assign)
    {
      next();
      if (*e == LC || *e == LI)
        *e = PSH;
      else
      {
        printf("%d: bad lvalue in assignment\n", line);
        exit(-1);
      }
      expr(Assign);
      *++e = ((ty = t) == CHAR) ? SC : SI;
    }
    else if (tk == Cond)
    {
      next();
      *++e = BZ;
      d = ++e;
      expr(Assign);
      if (tk == ':')
        next();
      else
      {
        printf("%d: conditional missing colon\n", line);
        exit(-1);
      }
      *d = (int)(e + 3);
      *++e = JMP;
      d = ++e;
      expr(Cond);
      *d = (int)(e + 1);
    }
    else if (tk == Lor)
    {
      next();
      *++e = BNZ;
      d = ++e;
      expr(Lan);
      *d = (int)(e + 1);
      ty = INT;
    }
    else if (tk == Lan)
    {
      next();
      *++e = BZ;
      d = ++e;
      expr(Or);
      *d = (int)(e + 1);
      ty = INT;
    }
    else if (tk == Or)
    {
      next();
      *++e = PSH;
      expr(Xor);
      *++e = OR;
      ty = INT;
    }
    else if (tk == Xor)
    {
      next();
      *++e = PSH;
      expr(And);
      *++e = XOR;
      ty = INT;
    }
    else if (tk == And)
    {
      next();
      *++e = PSH;
      expr(Eq);
      *++e = AND;
      ty = INT;
    }
    else if (tk == Eq)
    {
      next();
      *++e = PSH;
      expr(Lt);
      *++e = EQ;
      ty = INT;
    }
    else if (tk == Ne)
    {
      next();
      *++e = PSH;
      expr(Lt);
      *++e = NE;
      ty = INT;
    }
    else if (tk == Lt)
    {
      next();
      *++e = PSH;
      expr(Shl);
      *++e = LT;
      ty = INT;
    }
    else if (tk == Gt)
    {
      next();
      *++e = PSH;
      expr(Shl);
      *++e = GT;
      ty = INT;
    }
    else if (tk == Le)
    {
      next();
      *++e = PSH;
      expr(Shl);
      *++e = LE;
      ty = INT;
    }
    else if (tk == Ge)
    {
      next();
      *++e = PSH;
      expr(Shl);
      *++e = GE;
      ty = INT;
    }
    else if (tk == Shl)
    {
      next();
      *++e = PSH;
      expr(Add);
      *++e = SHL;
      ty = INT;
    }
    else if (tk == Shr)
    {
      next();
      *++e = PSH;
      expr(Add);
      *++e = SHR;
      ty = INT;
    }
    else if (tk == Add)
    {
      next();
      *++e = PSH;
      expr(Mul);
      if ((ty = t) > PTR)
      {
        *++e = PSH;
        *++e = IMM;
        *++e = sizeof(int);
        *++e = MUL;
      }
      *++e = ADD;
    }
    else if (tk == Sub)
    {
      next();
      *++e = PSH;
      expr(Mul);
      if (t > PTR && t == ty)
      {
        *++e = SUB;
        *++e = PSH;
        *++e = IMM;
        *++e = sizeof(int);
        *++e = DIV;
        ty = INT;
      }
      else if ((ty = t) > PTR)
      {
        *++e = PSH;
        *++e = IMM;
        *++e = sizeof(int);
        *++e = MUL;
        *++e = SUB;
      }
      else
        *++e = SUB;
    }
    else if (tk == Mul)
    {
      next();
      *++e = PSH;
      expr(Inc);
      *++e = MUL;
      ty = INT;
    }
    else if (tk == Div)
    {
      next();
      *++e = PSH;
      expr(Inc);
      *++e = DIV;
      ty = INT;
    }
    else if (tk == Mod)
    {
      next();
      *++e = PSH;
      expr(Inc);
      *++e = MOD;
      ty = INT;
    }
    else if (tk == Inc || tk == Dec)
    {
      if (*e == LC)
      {
        *e = PSH;
        *++e = LC;
      }
      else if (*e == LI)
      {
        *e = PSH;
        *++e = LI;
      }
      else
      {
        printf("%d: bad lvalue in post-increment\n", line);
        exit(-1);
      }
      *++e = PSH;
      *++e = IMM;
      *++e = (ty > PTR) ? sizeof(int) : sizeof(char);
      *++e = (tk == Inc) ? ADD : SUB;
      *++e = (ty == CHAR) ? SC : SI;
      *++e = PSH;
      *++e = IMM;
      *++e = (ty > PTR) ? sizeof(int) : sizeof(char);
      *++e = (tk == Inc) ? SUB : ADD;
      next();
    }
    else if (tk == Brak)
    {
      next();
      *++e = PSH;
      expr(Assign);
      if (tk == ']')
        next();
      else
      {
        printf("%d: close bracket expected\n", line);
        exit(-1);
      }
      if (t > PTR)
      {
        *++e = PSH;
        *++e = IMM;
        *++e = sizeof(int);
        *++e = MUL;
      }
      else if (t < PTR)
      {
        printf("%d: pointer type expected\n", line);
        exit(-1);
      }
      *++e = ADD;
      *++e = ((ty = t - PTR) == CHAR) ? LC : LI;
    }
    else
    {
      printf("%d: compiler error tk=%d\n", line, tk);
      exit(-1);
    }
  }
}

// 语句
void stmt()
{
  int *a, *b;

  if (tk == If)
  {
    next();
    if (tk == '(')
      next();
    else
    {
      printf("%d: open paren expected\n", line);
      exit(-1);
    }
    expr(Assign);
    if (tk == ')')
      next();
    else
    {
      printf("%d: close paren expected\n", line);
      exit(-1);
    }
    *++e = BZ;
    b = ++e;
    stmt();
    if (tk == Else)
    {
      *b = (int)(e + 3);
      *++e = JMP;
      b = ++e;
      next();
      stmt();
    }
    *b = (int)(e + 1);
  }
  else if (tk == While)
  {
    next();
    a = e + 1;
    if (tk == '(')
      next();
    else
    {
      printf("%d: open paren expected\n", line);
      exit(-1);
    }
    expr(Assign);
    if (tk == ')')
      next();
    else
    {
      printf("%d: close paren expected\n", line);
      exit(-1);
    }
    *++e = BZ;
    b = ++e;
    stmt();
    *++e = JMP;
    *++e = (int)a;
    *b = (int)(e + 1);
  }
  else if (tk == Return)
  {
    next();
    if (tk != ';')
      expr(Assign);
    *++e = LEV;
    if (tk == ';')
      next();
    else
    {
      printf("%d: semicolon expected\n", line);
      exit(-1);
    }
  }
  else if (tk == '{')
  {
    next();
    while (tk != '}')
      stmt();
    next();
  }
  else if (tk == ';')
  {
    next();
  }
  else
  {
    expr(Assign);
    if (tk == ';')
      next();
    else
    {
      printf("%d: semicolon expected\n", line);
      exit(-1);
    }
  }
}

// 主函数
int main(int argc, char **argv) { 
    int fd, bt, ty, *idmain;
    int i, *t;  
    NEXT_CMD_ARGV;
    if (argc > 0 && GET_ARGV[0] == '-' && GET_ARGV[1] == 's') {
        src = TRUE;
        NEXT_CMD_ARGV;
    }
    if (argc > 0 && GET_ARGV[0] == '-' && GET_ARGV[1] == 'd') {
        debug = TRUE;
        NEXT_CMD_ARGV;
    }
    if (argc < 1) {
        printf("Hello dugu complier! The version is %s\n", DUGU_VERSION);
        printf("usage: dugu [-s] [-d] file ...\n");
        return -1;
    }
    if ( (fd = open(GET_ARGV, 0)) < 0) {
        printf("cound not open (%s)\n", GET_ARGV);
        return MAIN_FUNC_RETURN_VAL;
    }
    varibles_malloc();
    // 所有的c关键字
    p = "char else enum if int return sizeof while "
      "open read close printf malloc free memset memcmp exit void main";
    
    printf("compile code...\n");

    i = Char;
    while (i <= While) {
        // add keywords to symbol table (向字符表添加关键字)
        next();
        id[Tk] = i++;
    }

    printf("compile code2...\n");

    i = OPEN;
    while (i <= EXIT) {
        // add library to symbol table (向字符表添加库)
        next();
        id[Class] = Sys;
        id[Type] = Int;
        id[Val] = i++;
    }
    next(); id[Tk] = Char;  // handle void type
    next(); idmain = id;    // keep track of main

    if (!(lp = p = malloc(POOL_SIZE))) {
        printf("could not malloc (%d) source area\n", POOL_SIZE);
        return -1;
    }

    // 读取文件词素流
    printf("read code...\n");
    if ( (i = read(fd, p, POOL_SIZE - 1)) <= 0) {
        printf("read() return %d\n", i);
        return -1;
    }
    p[i] = 0;
    close(fd);

    // prase declarations (prase的声明) 语法分析器
    printf("prase code...\n");
    line = 1;
    next();
    while (tk) {
        bt = INT;
        if (tk == Int) {
            next();
        }
        else if (tk == Char) {
            next();
            bt = CHAR;
        }
        else if (tk == Enum) {
            next();
            if (tk != '{')
                next();
            if (tk == '{') {
                next();
                i = 0;
                while (tk != '}') {
                    if (tk != Id) {
                        printf("%d: bad enum identifier %d", line, tk);
                        return -1;
                    }
                    next();
                    if (tk == Assign) {
                        next();
                        if (tk != Num) {
                            printf("%d: bad enum initializer\n", line);
                            return -1;
                        }
                        i = ival;
                        next();
                    }
                    id[Class] = Num;
                    id[Type] = INT;
                    id[Val] = i++;
                    if (tk == ',') 
                        next();            
                }
                next();
            }       
        }
        while (tk != ';' && tk != '}') {
            ty = bt;
            while (tk == Mul) {
                next();
                ty = ty + PTR;
            }
            if (tk != Id) {
                printf("%d: bad global declaration\n", line);
                return -1;
            }
            if (id[Class]) {
                printf("%d: duplicate global definition\n", line);
                return -1;
            }
            next();
            id[Type] = ty;
            // function 
            if (tk == '(') {
                id[Class] = Fun;
                id[Val] = (int)(e + 1);
                next();
                i = 0;
                while (tk != ')') {
                    ty = INT;
                    if (tk == Int) {
                        next();
                    }
                    else if (tk == Char) {
                        next();
                        ty = CHAR;
                    }
                    while (tk == Mul) {
                        next();
                        ty = ty + PTR;
                    }
                    if (tk != Id) {
                        printf("%d: bad parameter declaration\n", line);
                        return -1;
                    }
                    if (id[Class] == Loc) {
                        printf("%d: duplicate parameter definition\n", line);
                        return -1;
                    }
                    id[HClass] = id[Class];
                    id[Class] = Loc;
                    id[Htype] = id[Type];
                    id[Type] = ty;
                    id[HVal] = id[Val];
                    id[Val] = i++;
                    next();
                    if (tk == ',') {
                        next();
                    }
                }
                next();
                if (tk != '{') {
                    printf("%d: bad function definition\n", line);
                    return -1;
                }
                loc = ++i;
                next();
                while (tk == Int || tk == Char) {
                    bt = (tk == Int) ? INT : CHAR;
                    next();
                    while (tk != ';') {
                        ty = bt;
                            while (tk == Mul) {
                                next();
                                ty = ty + PTR;
                            }
                            if (id[Class] == Loc) {
                                printf("%d: duplicate local definition\n", line);
                                return -1;
                            }
                            id[HClass] = id[Class];
                            id[Class] = Loc;
                            id[Htype] = id[Type];
                            id[Type] = ty;
                            id[HVal] = id[Val];
                            id[Val] = ++i;
                            next();
                            if (tk == ',') {
                                next();
                            }
                        }
                        next();
                }
                *++e = ENT;
                *++e = i - loc;
                while (tk != '}')
                    stmt();
                *++e = LEV;
                id = sym; // unwind symbol table locals (展开本地符号表)
                while (id[Tk]) {
                    if (id[Class] == Loc) {
                        id[Class] = id[HClass];
                        id[Type] = id[Htype];
                        id[Val] = id[HVal];
                    }
                    id = id + Idsz;
                }
            }
            else {
                id[Class] = Glo;
                id[Val] = (int)data;
                data = data + sizeof(int);
            }
            if (tk == ',')
                next();
        }
        next();
    } 

    // 查找是否存在程序运行的起点 main() 函数
    if (!(pc = (int *)idmain[Val])) {
        printf("main() not defined\n");
        return -1;
    }

    if (src)
        return 0;

    // setup stack (设置堆栈)
    bp = sp = (int *)((int)sp + POOL_SIZE);
    *--sp = EXIT;
    *--sp = PSH;
    t = sp;
    *--sp = argc;
    *--sp = (int)argv;
    *--sp = (int)t;

    // run compile code in vm...
    printf("run code...\n");
    while(1) {
        i = *pc++;
        ++cycle;
        if (debug) {
            printf("%d> %.4s", cycle, 
                &"LEA ,IMM ,JMP ,JSR ,BZ  ,BNZ ,ENT ,ADJ ,LEV ,LI  ,LC  ,SI  ,SC  ,PSH ,"
              "OR  ,XOR ,AND ,EQ  ,NE  ,LT  ,GT  ,LE  ,GE  ,SHL ,SHR ,ADD ,SUB ,MUL ,DIV ,MOD ,"
              "OPEN,READ,CLOS,PRTF,MALC,FREE,MSET,MCMP,EXIT,"[i * 5]);
            i <= ADJ ? printf(" %d\n", pc) : printf("\n");       
        }
        if (i == LEA)
            a = (int)(bp + *pc++);  // load local address (加载本地地址)
        else if (i == IMM)
            a = *pc++;              // load global address or immediate (加载全局地址或立即数)
        else if (i == JMP)
            pc = (int *)*pc;        // jump
        else if (i == JSR) {
            *--sp = (int)(pc + 1);
            pc = (int *)*pc;
        }  // jump to subroutine
        else if (i == BZ) 
            pc = a ? pc + 1 : (int *)*pc;
        else if (i == BNZ)
            pc = a ? (int *)*pc : pc + 1;
        else if (i == ENT) {
            *--sp = (int)bp;
            bp = sp;
            sp = sp - *pc++;
        } // enter subroutine
        else if (i == ADJ)
            sp = sp + *pc++;    // stack adjust
        else if (i == LEV) {
            sp = bp;
            bp = (int *)*sp++;
            pc = (int *)*sp++;
        } // leave subroutine
        else if (i == LI)
            a = *(int *)a;   // load int
        else if (i == LC)
            a = *(char *)a;  // load char
        else if (i == SI)
            *(int *)*sp++ = a; // store int
        else if (i == SC) 
            a = *(char *)*sp++ = a;
        else if (i == PSH)
            *--sp = a;     // push

        else if (i == OR)
            a = *sp++ | a;
        else if (i == XOR)
            a = *sp++ ^ a;
        else if (i == AND)
            a = *sp++ & a;
        else if (i == EQ)
            a = *sp++ == a;
        else if (i == NE)
            a = *sp++ != a;
        else if (i == LT)
            a = *sp++ < a;
        else if (i == GT)
            a = *sp++ > a;
        else if (i == LE)
            a = *sp++ <= a;
        else if (i == GE)
            a = *sp++ >= a;
        else if (i == SHL)
            a = *sp++ << a;
        else if (i == SHR)
            a = *sp++ >> a;
        else if (i == ADD)
            a = *sp++ + a;
        else if (i == SUB)
            a = *sp++ - a;
        else if (i == MUL)
            a = *sp++ * a;
        else if (i == DIV)
            a = *sp++ / a;
        else if (i == MOD)
            a = *sp++ % a;
        
        else if (i == OPEN)
            a = open((char *)sp[1], *sp);
        else if (i == READ)
            a = read(sp[2], (char *)sp[1], *sp);
        else if (i == CLOS)
            a = close(*sp);
        else if (i == PRTF) {
            t = sp + pc[1];
            a = printf((char *)t[-1], t[-2], t[-3], t[-4], t[-5], t[-6]);
        }
        else if (i == MALC)
            a = (int)malloc(*sp);
        else if (i == FREE)
            free((void *)*sp);
        else if (i == MSET)
            a = (int)memset((char *)sp[2], sp[1], *sp);
        else if (i == MCMP)
            a = memcmp((char *)sp[2], (char *)sp[1], *sp);
        else if (i == EXIT) {
            printf("exit(%d) cycle = %d\n", *sp, cycle);
            printf("run code finished\n");
            return *sp;
        }
        else {
            printf("unknown instruction = %d! cycle = %d\n", i, cycle);
        }
    }

    varibles_free();
    return MAIN_FUNC_RETURN_VAL;
}
