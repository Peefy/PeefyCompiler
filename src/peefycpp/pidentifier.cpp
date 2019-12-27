
#include "pidentifier.h"

#include <regex>

#define IS_ID_START_CHAR(c) (\
              (c >= 'a' && c <= 'z')\
               || (c >= 'A' && c <= 'Z')\
               || c == '_'\
               || (c >= 128))

#define IS_ID_CHAR(c) (\
              (c >= 'a' && c <= 'z')\
               || (c >= 'A' && c <= 'Z')\
               || (c >= '0' && c <= '9')\
               || c == '_'\
               || (c >= 128))

BEGIN_PEEFY_NAMESPACE

// 关键字标识符，变量的命名不能与标识符重合
static const char* const keywords[] = {
      "char", "else", "enum", " if", "int", "return", "sizeof", "while", "for", "do", "switch", "case",
      "open", "read", "close", "printf", "malloc", "free", "memset", "memcmp", "exit", "void", "main", 
      "var", "auto", "where", "in", "out", "typedef", "typename", "nameof", "string",
      "float", "double", "uint", "uint8", "uint16", "uint32", "uint64", "int8", "int16", "int32", "int64", "float32", "float64"
      "try", "catch", "throw", "raise", "except", "error", "operator", "nil", "none", "null", "nullptr", "None", 
      "override", "virtual", "async", "await", "export", "import", "do", "repeat", "until", "do", "begin", "end", "goto", "pass",
      "require", "from", "to", "in", "out", "final", "const", "static", "local"
      "::", "!=", "==", "<=", ">=", "<<", ">>", "||", "&&"
};

// 符号表



END_PEEFY_NAMESPACE
