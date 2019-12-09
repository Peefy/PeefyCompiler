
#ifndef __P_SYMBOL_TABLE_H__
#define __P_SYMBOL_TABLE_H__

#include <string>
#include <memory>
#include <mutex>

#include "pidentifier.h"
#include "util.h"

using namespace std;

BEGIN_PEEFY_NAMESPACE

struct SymbolTableEntry {
    string lexptr;
    int token;
};

template<typename _TableValue, typename _SymbolValue>
class SymbolTableBase
{
public:
    using tablebval_type = _TableValue;
    using id_type = _SymbolValue;
    typedef shared_ptr<SymbolTableBase<tablebval_type, id_type> > Ptr;
private:
    unordered_set<PKeyword> _table;
    static mutex _mutex;  
    static Ptr self;
private:
    SymbolTableBase() = default;
    SymbolTableBase(SymbolTableBase&)=delete;
    SymbolTableBase& operator=(const SymbolTableBase&)=delete;
public:
    virtual ~SymbolTableBase() = default;
public:
    
    bool insert(tablebval_type& val);
    bool isintable(tablebval_type& val);
    static Ptr & instance() {
        lock_guard<mutex> lk(_mutex);
        if (self == nullptr) {
            self = make_shared<SymbolTableBase<_TableValue> >();
        }
        return self;
    }
};

using SymbolTable = SymbolTableBase<SymbolTableEntry, PKeyword>;

END_PEEFY_NAMESPACE


#endif

