
#include <string>
#include <memory>
#include <mutex>

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
	static Ptr _self;
private:
	SymbolTableBase() = default;
	SymbolTableBase(SymbolTableBase&) = delete;
	SymbolTableBase& operator=(const SymbolTableBase&) = delete;
public:
	virtual ~SymbolTableBase() = default;
public:

	bool insert(tablebval_type& val);
	bool isintable(tablebval_type& val);
	static Ptr& instance() {
		lock_guard<mutex> lk(_mutex);
		if (_self == nullptr) {
			_self = make_shared<SymbolTableBase<_TableValue> >();
		}
		return _self;
	}
};

template<typename _TableValue, typename _SymbolValue>
SymbolTableBase<_TableValue, _SymbolValue>::Ptr SymbolTableBase<_TableValue, _SymbolValue>::_self = nullptr;

template<typename _TableValue, typename _SymbolValue>
bool SymbolTableBase<_TableValue, _SymbolValue>::insert(tablebval_type& val)
{
	return false;
}

template<typename _TableValue, typename _SymbolValue>
bool SymbolTableBase<_TableValue, _SymbolValue>::isintable(tablebval_type& val)
{
	return false;
}
