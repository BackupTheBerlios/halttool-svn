
#include <string>

#include "Reference.h"
#include "Processor.h"
#include "Memory.h"

using namespace std;

void Reference::init()
	{
	switch ( mode )
		{
		case AddressIndirect:
			hasAddress = true;
//			address = g_cpu.a[ reg ];
			address = g_cpu.addrs.read( reg, Word::Address );
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

Reference::Reference( EA ea )
	: EA( ea.mode, ea.reg ), hasAddress( false ), hasValue( false )
	{
	init();
	}

Reference::Reference( short _mode, short _reg )
	: EA( _mode, _reg ), hasAddress( false ), hasValue( false )
	{
	init();
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
	if ( !hasValue )
		{
		switch ( mode )
			{
			case DataDirect:
				hasValue = true;
				value = g_cpu.regs.read( reg, Word::Data );
				break;
			case AddressDirect:
				hasValue = true;
//				value = g_cpu.a[ reg ];
				value = g_cpu.addrs.read( reg, Word::Address );
				break;
			case AddressIndirect:
				hasValue = true;
//				value = g_mem.read( g_cpu.a[ reg ], Word::Data );
				value = g_mem.read( g_cpu.addrs.read( reg, Word::Address ), Word::Data );
				break;
			case PostIncrement:
//				value = g_mem.read( g_cpu.a[ reg ], Word::Data );
//				++( g_cpu.a[ reg ]);
				{
				unsigned short address = g_cpu.addrs.read( reg, Word::Address );
				value = g_mem.read( address, Word::Data );
				g_cpu.addrs.write( reg, Word::Address, address + 1 );
				break;
				}
			case PreDecrement:
//				--( g_cpu.a[ reg ]);
//				value = g_mem.read( g_cpu.a[ reg ], Word::Data );
				{
				unsigned short address = g_cpu.addrs.read( reg, Word::Address );
				value = g_mem.read( address - 1, Word::Data );
				g_cpu.addrs.write( reg, Word::Address, address - 1 );
				break;
				}
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
//				g_cpu.a[ reg ] = newValue;
				g_cpu.addrs.write( reg, Word::Address, newValue );
				break;
			case AddressIndirect:
//				g_mem.write( g_cpu.a[ reg ], Word::Data, newValue );
				g_mem.write( g_cpu.addrs.read( reg, Word::Address ), Word::Data, newValue );
				break;
			case PostIncrement:
//				g_mem.write( g_cpu.a[ reg ], Word::Data, newValue );
//				++( g_cpu.a[ reg ]);
				{
				unsigned short address = g_cpu.addrs.read( reg, Word::Address );
				g_mem.write( address, Word::Data, newValue );
				g_cpu.addrs.write( reg, Word::Address, address + 1 );
				break;
				}
			case PreDecrement:
//				--( g_cpu.a[ reg ]);
//				g_mem.write( g_cpu.a[ reg ], Word::Data, newValue );
				{
				unsigned short address = g_cpu.addrs.read( reg, Word::Address );
				g_mem.write( address - 1, Word::Data, newValue );
				g_cpu.addrs.write( reg, Word::Address, address - 1 );
				break;
				}
			case Absolute:
				g_mem.write( address, Word::Data, newValue );
				break;
			default:
				;
			}
	else
		throw string("addressing mode not alterable");
	}
