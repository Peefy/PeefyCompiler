
#ifndef __P_OBJECT_H__
#define __P_OBJECT_H__

// peefy 对象库

#include <stdint.h>
#include <string>

#include "util.h"

using namespace std;

BEGIN_PEEFY_NAMESPACE

template <typename T>
struct PObjcetBase {
public:
    uint64_t refrence_count;
    uint64_t hashval;
    constexpr PObjcetBase() : 
        refrence_count(0),  
        hashval(0) {

    }
    T value;
private:
};

struct PObject : public PObjcetBase<int> {
private:
    PObject* next;
};

END_PEEFY_NAMESPACE



#endif
