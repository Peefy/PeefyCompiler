
#include "pidentifier.h"

static char* keywords = "char else enum if int return sizeof while for do switch case"
      "open read close printf malloc free memset memcmp exit void main "
      "var auto where in out typedef typename nameof string "
      "float double uint uint8 uint16 uint32 uint64 int8 int16 int32 int64 float32 float64"
      "try catch throw raise except error operator";

static unordered_set<PKeyword> symbolTable = {
      PKeyword("char"), 
      PKeyword("else"), 
      PKeyword("enum"), 
      PKeyword("if"), 
      PKeyword("int"), 
      PKeyword("return"), 
      PKeyword("sizeof"), 
      PKeyword("while"), 
      PKeyword("for"), 
      PKeyword("do"), 
      PKeyword("switch"), 

      PKeyword("open"), 
      PKeyword("read"), 
      PKeyword("close"), 
      PKeyword("printf"), 
      PKeyword("malloc"), 
      PKeyword("free"), 
      PKeyword("memset"), 
      PKeyword("memcmp"), 
      PKeyword("exit"), 

      PKeyword("void"),
      PKeyword("main"),
      PKeyword("var"),
      PKeyword("auto"),
      PKeyword("where"),
      PKeyword("in"),
      PKeyword("out"),
      PKeyword("typedef"),
      PKeyword("typename"),
      PKeyword("nameof"),
      PKeyword("string"),
      PKeyword("float"),
      PKeyword("double"),

      PKeyword("uint"),
      PKeyword("uint8"),
      PKeyword("uint16"),
      PKeyword("uint32"),
      PKeyword("uint64"),

      PKeyword("int8"),
      PKeyword("int16"),
      PKeyword("int32"),
      PKeyword("int64"),

      PKeyword("float32"),
      PKeyword("float64"),
      PKeyword("try"),
      PKeyword("catch"),
      PKeyword("throw"),
      PKeyword("raise"),
      PKeyword("except"),
      PKeyword("error"),
      PKeyword("operator")

};

inline bool is_in_table(string& id) {
      return symbolTable.find(PKeyword(id)) != symbolTable.end();
}
