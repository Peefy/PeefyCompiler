package main

type SymbolTableEntry struct {
	str string
	token int
}

type SymbolTableBase struct {
	table map[string] SymbolTableEntry
}	

func (s *SymbolTableBase) Insert(item SymbolTableEntry)  {
	s.table = make(map[string] SymbolTableEntry, 0)
}

func (s *SymbolTableBase) Find(item SymbolTableEntry) bool {
	s.table = make(map[string] SymbolTableEntry, 0)
	return false
}
