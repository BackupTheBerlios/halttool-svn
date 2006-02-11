
#ifndef Reference_Interface
#define Reference_Interface

#include "EA.h"

class Reference : public EA
	{
	unsigned short address;
	short value;

	bool hasAddress;
	bool hasValue;
	bool dirty;

public:
	Reference( short _mode, short _reg = 0 );

	short getAddress();
	short read();
	void write( short newValue );
	};

#endif
