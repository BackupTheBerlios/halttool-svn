
#include <iostream>
#include <string>

#include "Reference.h"
#include "Processor.h"
#include "Memory.h"

using namespace std;

Reference::Reference( short _mode, short _reg )
	: EA( static_cast<EA::Mode>(_mode), _reg ),
	  hasAddress( false ), hasValue( false )
	{
	switch ( mode )
		{
		case AddressIndirect:
			hasAddress = true;
			address = g_cpu.a[ reg ];
			break;
		case Absolute:
			hasAddress = true;
			address = g_cpu.fetch();
			break;
		case Immediate:
			hasValue = true;
			value = g_cpu.fetch();
			break;
		default:
			;
		}
	}

short Reference::getAddress()
	{
	if ( hasAddress )
		return address;
	else
		throw string("I have no address");
	}

short Reference::read()
	{
	if ( not hasValue )
		{
		switch ( mode )
			{
			case DataDirect:
				hasValue = true;
				value = g_cpu.regs.read( reg, Word::Data );
				break;
			case AddressDirect:
				hasValue = true;
				value = g_cpu.a[ reg ];
				break;
			case AddressIndirect:
				hasValue = true;
				value = g_mem.read( g_cpu.a[ reg ], Word::Data );
				break;
			case PostIncrement:
				value = g_mem.read( g_cpu.a[ reg ], Word::Data );
				++( g_cpu.a[ reg ]);
				break;
			case PreDecrement:
				--( g_cpu.a[ reg ]);
				value = g_mem.read( g_cpu.a[ reg ], Word::Data );
				break;
			case Absolute:
				hasValue = true;
				value = g_mem.read( address, Word::Data  );
				break;
			default:
				;
			}
		}
	return value;
	}

void Reference::write( short newValue )
	{
	if ( inCategory( alterable ))
		switch ( mode )
			{
			case DataDirect:
				g_cpu.regs.write( reg, Word::Data, newValue );
				break;
			case AddressDirect:
				g_cpu.a[ reg ] = newValue;
				break;
			case AddressIndirect:
				g_mem.write( g_cpu.a[ reg ], Word::Data, newValue );
				break;
			case PostIncrement:
				g_mem.write( g_cpu.a[ reg ], Word::Data, newValue );
				++( g_cpu.a[ reg ]);
				break;
			case PreDecrement:
				--( g_cpu.a[ reg ]);
				g_mem.write( g_cpu.a[ reg ], Word::Data, newValue );
				break;
			case Absolute:
				g_mem.write( address, Word::Data, newValue );
				break;
			default:
				;
			}
	else
		throw string("addressing mode not alterable");
	}
