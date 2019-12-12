
#ifndef __P_ERROR_H__
#define __P_ERROR_H__

#include "util.h"

#include <string>
#include <unordered_map>
#include <unordered_set>

using namespace std;

BEGIN_PEEFY_NAMESPACE

template <typename T>
struct PFlag {
    T val;
    T defaultVal;
    T* ptr;
    string description;
    inline bool operator==(T& other) {
        return val == other;
    }
    inline bool operator!=(T& other) {
        return val != other;
    }
};

class PCmdFlag
{
private:
    static unordered_map<string, string> symtb;
public:
    PCmdFlag(/* args */);
    ~PCmdFlag();
public:
    static PFlag<string> newString(const char * paras) {
        return PFlag<string>();
    }
    static PFlag<bool> newBoolean(const char * paras) {
        return PFlag<bool>();
    }
};

PCmdFlag::PCmdFlag(/* args */)
{
    
}

PCmdFlag::~PCmdFlag()
{
}


END_PEEFY_NAMESPACE

#endif
