
#ifndef __P_TOKEN_H__
#define __P_TOKEN_H__

// peefy 记号token库

#include "util.h"

#include <string>

using namespace std;

BEGIN_PEEFY_NAMESPACE

// 记号类型
enum class PTokenType {
    // 错误，什么都不是
    None = -1, 
    // 标识符 (变量名、数组名、函数名等)
    Identifier = 257,
    // 数字(整数)
    Integer,
    // 数字(浮点数)
    Float,
    // 字符
    Char,
    // 字符串
    String,
    // 操作符 @ $ # % ^ & * + - * / ++ -- += -= *= /= && || ~ ** ? . ' "
    Operator,
    // 关键字
    Keyword, 
    // () [] {} <>
    Brakets,
    // 换行
    Endline,
    // 句尾
    Over, 
    // 注释
    Comment,
    // 空白
    WhiteSpace,
    // 赋值
    Assign,
    // 函数
    Function,
    // 系统指令
    System,
    // 全局变量
    GlobalVaribale,
    // 局部变量
    LocalVaribale,
    // 枚举
    Enum,
    // 条件运算符 if
    If,
    // 条件运算符 else
    Else,
    // 循环运算符 for
    For,
    // 循环运算符while
    While,
    // 按位或 |
    Lor,
    // 按位与 & 
    Lan,
    // 按位取反 ~
    Lnon,
    // 逻辑取反 ! 
    Non,
    // 逻辑或 || 
    Or, 
    // 按位异或 ^
    Xor, 
    // 逻辑与 &&
    And, 
    // 是否等于 == 
    Eq, 
    // 是否不等 !=
    Ne, 
    // 小于 <
    Lt, 
    // 大于 >
    Gt,
    // 小于等于 <= 
    Le, 
    // 大于等于 >=
    Ge, 
    // 按位左移动 <<
    Shl, 
    // 按位右移动 >>
    Shr, 
    // 加法运算符 +
    Add, 
    // 减法运算符 -
    Sub, 
    // 乘法运算符 *
    Mul, 
    // 除法运算符 /
    Div, 
    // 求余运算符 %
    Mod, 
    // 自加运算符 ++
    Inc,
    // 自减运算符 -- 
    Dec,
    // 乘方运算符 **
    Pow,
    // ~  ++ -- += -= *= /= ? : ?? 
    // 返回
    Return,
    // 类型大小 
    Sizeof,
};

// 语义信息
struct SemInfo {
    double r;
    int i;
    string ts;
    int value;
};

// 词法分析的记号
template<typename T>
struct PToken {
public:
    PToken() noexcept = default;
    virtual ~PToken() noexcept = default;
    constexpr PToken(PToken& token) noexcept = default;
    constexpr PToken& operator=(PToken& token) noexcept = default;
    constexpr PToken& operator=(PToken& token) noexcept = default;
public:
    PTokenType type;
    T value;
    bool isSingleByteSymbol;
private:

};

using PTokenValue = PToken<SemInfo>;



END_PEEFY_NAMESPACE

#endif
