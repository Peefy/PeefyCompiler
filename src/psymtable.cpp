
#include "psymtable.h"

BEGIN_PEEFY_NAMESPACE

template<typename _TableValue, typename _SymbolValue>
SymbolTableBase<_TableValue, _SymbolValue>::Ptr SymbolTableBase<_TableValue, _SymbolValue>::_self = nullptr;

template<typename _TableValue, typename _SymbolValue>
inline bool SymbolTableBase<_TableValue, _SymbolValue>::insert(tablebval_type& val)
{
    this->_table.insert(val);
	return true;
}

template<typename _TableValue, typename _SymbolValue>
inline bool SymbolTableBase<_TableValue, _SymbolValue>::isintable(tablebval_type& val)
{
	return this->_table.find(val) != this->_table.end();
}


void init_table() {
    
}

END_PEEFY_NAMESPACE


