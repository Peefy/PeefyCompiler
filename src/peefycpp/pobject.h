
#ifndef __P_OBJECT_H__
#define __P_OBJECT_H__

// peefy 对象库

#include <stdint.h>
#include <string>

#include "util.h"

using namespace std;

BEGIN_PEEFY_NAMESPACE

struct PObject {
public:
    PObject* next;
    int intpreter;
    bool isMarked;
private:
    int _private_count;
};

template <typename T>
struct PObjcetWithT : public PObject {
public:
    uint64_t refrence_count;
    uint64_t hashval;
    constexpr PObjcetWithT() : 
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
