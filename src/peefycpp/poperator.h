
#ifndef __P_OPERATOR_H__
#define __P_OPERATOR_H__

// peefy 操作符库

#include "util.h"

BEGIN_PEEFY_NAMESPACE

class POperator
{
private:
    
public:
    POperator() = default;
    virtual ~POperator() = default;
};

POperator::POperator()
{
}

POperator::~POperator()
{
}


END_PEEFY_NAMESPACE

#endif

