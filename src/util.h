
#ifndef __UTIL_H__
#define __UTIL_H__

// 字符是否是十进制的数字字符
#define IS_DIGIT(c)       ((c) >= '0' && (c) <= '9') 
// 字符是否是八进制的数字字符
#define IS_DIGIT_OCTAL(c) ((c) >= '0' && (c) <= '7') 
// 字符是否是八进制的数字字符
#define IS_DIGIT_HEX(c)   (IS_DIGIT(c) || ((c) >= 'a' && (c) <= 'f') || ((c) >= 'A' && (c) <= 'F'))
// 字符是否是大写字母
#define IS_UPPER_CHAR(c)  ((c) >= 'A' && (c) <= 'Z')
// 字符是否是小写字母
#define IS_LOWER_CHAR(c)  ((c) >= 'a' && (c) <= 'z')
// 字符是否是英文字母
#define IS_ALPHA(c)       (((c) >= 'a' && (c) <= 'z') || ((c) >= 'A' && (c) <= 'Z'))
// 是否为换行符
#define IS_NEW_LINE(c)    ((c) == '\n' || (c) == '\r')
// 是否是空白字符
#define IS_WHITE_SPACE(c) ((c) == ' ' || (c) == '\f' || (c) == '\t' || (c) == '\v')

#define ARR_SIZE(arr)     (sizeof(arr) / sizeof(arr[0]))

#define and &&
#define or  ||
#define xor ^
#define bitand &
#define bitor |
#define mod %
#define div /
#define mul *
#define add +
#define sub -

#define MAIN_FUNC_RETURN_VAL -1

#ifndef TRUE
#define TRUE 1
#endif

#ifndef FALSE
#define FALSE 1
#endif

#define BEGIN_PEEFY_NAMESPACE namespace peefy { 
#define END_PEEFY_NAMESPACE }

#endif
