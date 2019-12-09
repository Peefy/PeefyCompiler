
#ifndef __P_VM_H__
#define __P_VM_H__

#include "util.h"

BEGIN_PEEFY_NAMESPACE

enum class PVMCommandType {
    LEA ,
    IMM ,
    // 跳转指令
    JMP ,
    JSR ,
    BZ  ,
    BNZ ,
    ENT ,
    ADJ ,
    LEV ,
    LI  ,
    LC  ,
    SI  ,
    SC  ,
    // 压栈
    PSH ,
    OR  ,
    XOR ,
    AND ,
    EQ  ,
    NE  ,
    LT  ,
    GT  ,
    LE  ,
    GE  ,
    SHL ,
    SHR ,
    // 加
    ADD ,
    // 减
    SUB ,
    // 乘
    MUL ,
    // 除
    DIV ,
    // 求余
    MOD ,
    OPEN,READ,CLOS,PRTF,MALC,FREE,MSET,MCMP,EXIT,
};

struct PVMCommand
{
public:
    PVMCommand() noexcept = default;
    virtual ~PVMCommand() noexcept = default;
    constexpr PVMCommand(PVMCommand& token) noexcept = default;
    constexpr PVMCommand& operator=(PVMCommand& token) noexcept = default;
    constexpr PVMCommand& operator=(PVMCommand& token) noexcept = default;
public:
    PVMCommandType command;
};

END_PEEFY_NAMESPACE




#endif
