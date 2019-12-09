
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
	using symbol_type = _SymbolValue;
	typedef shared_ptr<SymbolTableBase<tablebval_type, symbol_type> > Ptr;
private:
	unordered_set<PKeyword> _table;
	static mutex _mutex;
	static Ptr _self;
private:
	SymbolTableBase() = default;
	SymbolTableBase(SymbolTableBase&) = delete;
	SymbolTableBase& operator=(const SymbolTableBase&) = delete;
public:
	virtual ~SymbolTableBase() = default;
public:

	inline bool insert(tablebval_type& val);
	inline bool isintable(tablebval_type& val);
	constexpr static Ptr& instance() {
		lock_guard<mutex> lk(_mutex);
		if (_self == nullptr) {
			_self = make_shared<SymbolTableBase<_TableValue> >();
		}
		return _self;
	}
};


END_PEEFY_NAMESPACE


#endif

