
#include "SymbolTable.h"
#include "Sequence.h"

using namespace std;

SymbolTable g_symbolTable;

//	struct CrossReference
//		{
//		Sequence* sequence;
//		unsigned short offset;
//		};
//
//	map< string, Sequence* > namedSequences;
//	multimap< string, CrossReference > crossReferences;

void SymbolTable::bind()
	{
	for ( map<string,Sequence*>::const_iterator i  = namedSequences.begin();
												i != namedSequences.end(); ++i )
		{
		const string& name = i->first;
		const unsigned short address = i->second->address();
		}
	}
