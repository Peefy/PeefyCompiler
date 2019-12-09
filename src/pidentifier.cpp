
#include "pidentifier.h"

#include "util.h"

// 关键字标识符，变量的命名不能与标识符重合
static const char* const keywords[] = {
      "char", "else", "enum", " if", "int", "return", "sizeof", "while", "for", "do", "switch", "case",
      "open", "read", "close", "printf", "malloc", "free", "memset", "memcmp", "exit", "void", "main", 
      "var", "auto", "where", "in", "out", "typedef", "typename", "nameof", "string",
      "float", "double", "uint", "uint8", "uint16", "uint32", "uint64", "int8", "int16", "int32", "int64", "float32", "float64"
      "try", "catch", "throw", "raise", "except", "error", "operator", 
      "override", "virtual", "async", "await", "export", "import", "do", "repeat", "until", "do", "begin", "end", "goto",
      "::", "!=", "==", "<=", ">=", "<<", ">>", "||", "&&"
};

// 符号表
static unordered_set<PKeyword> symbolTable; 

void build_table(unordered_set<PKeyword>& table) {
    table.clear();
    for (const auto & key : keywords) {
          table.insert(PKeyword(key));
    }
}

inline bool is_in_table(string& id) {
    return symbolTable.find(PKeyword(id)) != symbolTable.end();
}
