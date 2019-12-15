
#ifndef __P_LEXICAL_H__
#define __P_LEXICAL_H__

// peefy 词法分析器

/*
* 状态机:
* 状态转移图:
*/

#include "util.h"
#include "ptoken.h"

BEGIN_PEEFY_NAMESPACE

// 词法分析状态机
class PlexicalState
{
private:
    
public:
    PlexicalState();
    ~PlexicalState();
public:
    int current_char;
    int line_number;
    int last_line;
    PTokenValue current_token;  //输入字符/词素流
    PTokenValue lookahead;  // 
    string source;  // 当前源名称
    string enbn;  // 环境变量名称
public:
    PTokenValue nextToken();
};

END_PEEFY_NAMESPACE




#endif
