
#ifndef __P_OBJECT_H__
#define __P_OBJECT_H__

#include <stdint.h>
#include <string>

using namespace std;

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

};

#endif
