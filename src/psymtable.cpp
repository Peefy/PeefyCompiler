
#include "psymtable.h"

BEGIN_PEEFY_NAMESPACE

template<typename _TableValue, typename _SymbolValue>
SymbolTableBase<_TableValue, _SymbolValue>::Ptr SymbolTableBase<_TableValue, _SymbolValue>::self = nullptr;

void init_table() {
    
}

END_PEEFY_NAMESPACE


