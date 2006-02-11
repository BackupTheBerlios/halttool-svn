
#include "EA.h"

short EA::category[] = {
//-----------------------------------------------------------
	data |    0   |    0    | alterable,	// DataDirect
	  0  |    0   |    0    | alterable,	// AddressDirect
	data | memory | control | alterable,	// AddressIndirect
	data | memory |    0    | alterable,	// PostIncrement
	data | memory |    0    | alterable,	// PreDecrement
	data | memory | control | alterable,	// Absolute
	data | memory |    0    |     0,     	// Immediate
//-----------------------------------------------------------
	  0  |    0   |    0    |     0			// Unknown
	};

EA::EA( Mode _mode, short _reg )
	: mode(_mode ), reg(_reg )
	{ }

bool EA::inCategory( short flags )
	{
	return ( category[ mode ] & flags ) == flags;
	}
