
#ifndef __P_SYMBOL_TABLE_H__
#define __P_SYMBOL_TABLE_H__

#include <string>
#include <memory>
#include <mutex>
#include <type_traits>

#include "pidentifier.h"
#include "util.h"

using namespace std;

BEGIN_PEEFY_NAMESPACE

struct SymbolTableEntry {
    string str;
    int token;
};

template<typename _TableValue, typename _SymbolValue>
class SymbolTableBase
{
public:

	using tablebval_type = _TableValue;
	using symbol_type = _SymbolValue;
	using self_type = SymbolTableBase<tablebval_type, symbol_type>;
	typedef shared_ptr<SymbolTableBase<tablebval_type, symbol_type> > Ptr;
private:
	unordered_set<string> _table;
	static mutex _mutex;
	static Ptr _self;
private:
	SymbolTableBase() noexcept = default;
	SymbolTableBase(SymbolTableBase&) noexcept = delete;
	SymbolTableBase& operator=(const SymbolTableBase&) noexcept = delete;
public:
	virtual ~SymbolTableBase() = default;
public:
	inline bool insert(tablebval_type& val);
	inline bool isintable(tablebval_type& val);
	constexpr static Ptr& instance() {
		lock_guard<mutex> lk(_mutex);
		if (_self == nullptr) {
			_self = make_shared<self_type >();
		}
		return _self;
	}
};

template<typename _TableValue, typename _SymbolValue>
SymbolTableBase<_TableValue, _SymbolValue>::Ptr SymbolTableBase<_TableValue, _SymbolValue>::_self = nullptr;

template<typename _TableValue, typename _SymbolValue>
inline bool SymbolTableBase<_TableValue, _SymbolValue>::insert(tablebval_type& val)
{
    this->_table.insert(static_cast<string>(val.str));
	return true;
}

template<typename _TableValue, typename _SymbolValue>
inline bool SymbolTableBase<_TableValue, _SymbolValue>::isintable(tablebval_type& val)
{
	return this->_table.find(val) != this->_table.end();
}

END_PEEFY_NAMESPACE


#endif

