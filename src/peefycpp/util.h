
#ifndef __UTIL_H__
#define __UTIL_H__

#include <stdio.h>
#include <stdint.h>

// platform 

// DARWIN
#if defined(__APPLE__) && (defined(__GNUC__) || defined(__xlC__) || defined(__xlc__))
#  include <TargetConditionals.h>
#  if defined(TARGET_OS_MAC) && TARGET_OS_MAC
#    define I_OS_DARWIN
#    ifdef __LP64__
#      define I_OS_DARWIN64
#    else
#      define I_OS_DARWIN32
#    endif
#  else
#    error "not support this Apple platform"
#  endif
// ANDROID
#elif defined(__ANDROID__) || defined(ANDROID)
#  define I_OS_ANDROID
#  define I_OS_LINUX
// Windows
#elif !defined(SAG_COM) && (!defined(WINAPI_FAMILY) || WINAPI_FAMILY==WINAPI_FAMILY_DESKTOP_APP) && (defined(WIN64) || defined(_WIN64) || defined(__WIN64__))
#  define I_OS_WIN32
#  define I_OS_WIN64
#elif !defined(SAG_COM) && (defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__))
#  if defined(WINAPI_FAMILY)
#    ifndef WINAPI_FAMILY_PC_APP
#      define WINAPI_FAMILY_PC_APP WINAPI_FAMILY_APP
#    endif
#    if defined(WINAPI_FAMILY_PHONE_APP) && WINAPI_FAMILY==WINAPI_FAMILY_PHONE_APP
#      define I_OS_WINRT   // WinRT
#    elif WINAPI_FAMILY==WINAPI_FAMILY_PC_APP
#      define I_OS_WINRT   // WinRT
#    else
#      define I_OS_WIN32  // Win32
#    endif
#  else
#    define I_OS_WIN32   // Win32
#  endif
//CYGWIN
#elif defined(__CYGWIN__)
#  define I_OS_CYGWIN  // cygWin
// sun os
#elif defined(__sun) || defined(sun)
#  define I_OS_SUN     // Sun OS
// LINUX
#elif defined(__linux__) || defined(__linux)
#  define I_OS_LINUX   // Linux
// FREEBSD
#elif defined(__FreeBSD__) || defined(__DragonFly__) || defined(__FreeBSD_kernel__)
#  ifndef __FreeBSD_kernel__
#    define I_OS_FREEBSD   // FreeBSD
#  endif
#  define I_OS_FREEBSD_KERNEL // FreeBSD Kernel
// OPENBSD
#elif defined(__OpenBSD__)
#  define I_OS_OPENBSD // OpenBSD
// IBM AIX
#elif defined(_AIX)
#  define I_OS_AIX // aix
#else
#  error "not support this OS"
#endif

#if defined(I_OS_WIN32) || defined(I_OS_WIN64) || defined(I_OS_WINRT)
#  define I_OS_WIN  // Windows 
#endif

#if defined(I_OS_WIN)
#  undef I_OS_UNIX  // Unix
#elif !defined(I_OS_UNIX)
#  define I_OS_UNIX // Unix
#endif

#ifdef I_OS_DARWIN
#define I_OS_MAC   // darwin 
#endif
#ifdef I_OS_DARWIN32
#define I_OS_MAC32 // darwin 32
#endif
#ifdef I_OS_DARWIN64
#define I_OS_MAC64 // darwin 64
#endif


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
// 求数组的大小
#define ARR_SIZE(arr)     (sizeof(arr) / sizeof(arr[0]))

#define CONSOLE_SUCCESS (0)
#define CONSOLE_FAILURE (-1)

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
