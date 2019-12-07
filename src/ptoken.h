
#ifndef __P_TOKEN_H__
#define __P_TOKEN_H__

enum class PTokenType {
    // 错误，什么都不是
    None = 256, 
    // 标识符 (变量名、数组名、函数名等)
    Identifier,
    // 数字(整数)
    Integer,
    // 数字(浮点数)
    Float,
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
    WhiteSpace
};

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
private:

};


#endif
