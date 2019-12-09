
#ifndef __P_LEXICAL_H__
#define __P_LEXICAL_H__

#include "ptoken.h"

class PlexicalState
{
private:
    /* data */
public:
    PlexicalState(/* args */);
    ~PlexicalState();
public:
    int current_char;
    int line_number;
    int last_line;
    PTokenValue current_token;  //输入字符/词素流
    PTokenValue lookahead;  // 
    string source;  // 当前源名称
    string enbn;  // 环境变量名称
};


#endif
