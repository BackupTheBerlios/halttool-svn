
#ifndef halt_Memory
#define halt_Memory

#include <vector>

#include "Sequence.h"
#include "Program.h"

class Memory
	{
	std::vector< Word > contents;

public:
	void clear();
	
	// append machine code
	void operator << ( const Sequence& );
	void operator << ( Program& );

	unsigned short size() const;

	const Word& word( unsigned short address ) const;

	short read( unsigned short address, Word::Type ) const;
	void write( unsigned short address, Word::Type, short value );
	};

extern Memory g_mem;

#endif
