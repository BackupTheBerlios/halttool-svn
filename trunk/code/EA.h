
#ifndef halt_EA
#define halt_EA

struct EA
	{
	enum Mode
		{
		DataDirect,			// Dn
		AddressDirect,		// An
		AddressIndirect,	// (An)
		PostIncrement,		// (An)+
		PreDecrement,		// -(An)
		Absolute,			// (label) or (hex:100)
		Immediate,			// 1234
	//----------------------//
		Unknown
		};

	enum Category
		{
		data = 8,
		memory = 4,
		control = 2,
		alterable = 1
		};

	Mode mode;
	short reg;

	EA( short _mode = Unknown, short _reg = 0 );
	bool inCategory( short flags ); // bit-or multiple categories together to test at once

private:
	static short category[ Unknown + 1 ];
	};

#endif
