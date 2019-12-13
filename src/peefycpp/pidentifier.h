
#ifndef __P_TOKEN_H__
#define __P_TOKEN_H__

// peefy 标识符

#include <string>
#include <unordered_map>
#include <unordered_set>

#include "util.h"
#include "psymtable.h"

using namespace std;

BEGIN_PEEFY_NAMESPACE


template<typename T>
struct PIdentifier {
public:
    constexpr PIdentifier() noexcept = default;
    virtual ~PIdentifier() noexcept = default;
    constexpr PIdentifier(PIdentifier& token) noexcept = default;
    constexpr PIdentifier& operator=(PIdentifier& token) noexcept = default;
    constexpr PIdentifier& operator=(PIdentifier& token) noexcept = default;
public:
    T value;
private:
    
};

struct PKeyword : public PIdentifier<string>
{
public:
    explicit PKeyword(string& val) noexcept {
        this->value = val;
    }
    explicit PKeyword(string&& val) noexcept {
        this->value = val;
    }  
private:
    PKeyword() = default;
public:
    inline bool operator== (PKeyword& other) {
        return this->value == other.value;
    }
    inline bool operator!= (PKeyword& other) {
        return this->value != other.value;
    }
    inline int compare(PKeyword& other) {
        return strcmp(this->value.c_str(), other.value.c_str());
    }
private:
};

using SymbolTable = SymbolTableBase<peefy::SymbolTableEntry, peefy::PKeyword>;

END_PEEFY_NAMESPACE

#endif
