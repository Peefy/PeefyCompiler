
#ifndef __P_API_H__
#define __P_API_H__

// Peefy Compiler C API

#include <stdint.h>
#include <string>

using std::string;
using std::wstring;

#define pint8  int8_t
#define pint16 int16_t
#define pint32 int32_t
#define puint8  uint8_t
#define puint16 uint16_t
#define puint32 uint32_t

#define pstring string
#define wstring wstring 

#include "util.h"

#define PEEFY_API extern

extern "C" 
{

PEEFY_API int peefy_init();

}

#endif
