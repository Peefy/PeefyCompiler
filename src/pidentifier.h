
#ifndef __P_TOKEN_H__
#define __P_TOKEN_H__

#include <string>
#include <unordered_map>
#include <unordered_set>

using namespace std;

template<typename T>
struct PIdentifier {
public:
    PIdentifier() noexcept = default;
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
    PKeyword(string val) {
        this->value = val;
    } 
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



#endif
