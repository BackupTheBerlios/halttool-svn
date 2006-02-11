
#include "BitField.h"

BitField::BitField( short integer )
	: bits( integer ) { }

void BitField::insert( short newValue, unsigned pos, unsigned numBits )
	{
	short mask = 0xffff >> ( 16 - numBits );
	bits = ( bits & ~( mask << pos )) | (( newValue & mask ) << pos );
	}

short BitField::extract( unsigned pos, unsigned numBits )
	{
	short mask = 0xffff >> ( 16 - numBits );
	return ( bits >> pos ) & mask;
	}

short BitField::extend( unsigned pos, unsigned numBits )
	{
	short mask = 0xffff >> ( 16 - numBits );
	short xtend = ( bits >> pos ) & mask;
	if ( xtend >> ( numBits - 1 ))	//	if msb = 1
		xtend |= ~mask;				//		fill left with 1s
	return xtend;
	}
