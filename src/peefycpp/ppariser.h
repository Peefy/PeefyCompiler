
#ifndef __P_PARISER_H__
#define __P_PARISER_H__

// peefy 语法分析器

#include "util.h"

BEGIN_PEEFY_NAMESPACE

class PPariser
{
private:
public:
    PPariser() noexcept = default;
    virtual ~PPariser() = default;
};

END_PEEFY_NAMESPACE


#endif
