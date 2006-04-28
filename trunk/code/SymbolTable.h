
#ifndef halt_SymbolTable
#define halt_SymbolTable

#include <string>
#include <map>

class Sequence; // forward reference

struct CrossReference
	{
	Sequence* sequence;
	unsigned short offset;
	};

class SymbolTable
	{
	std::map< std::string, Sequence* > namedSequences;
	std::multimap< std::string, CrossReference > crossReferences;

public:
	void bind();
	};

extern SymbolTable g_symbolTable;

#endif
