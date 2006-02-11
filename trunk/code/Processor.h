
#ifndef halt_Processor
#define halt_Processor

#include "BitField.h"
#include "Memory.h"
#include <iostream>

using namespace std;

// A simple 16-bit processor
class Processor
	{
//	Word d[8];				// data registers

	Memory regs;			// data registers
	unsigned short a[8];	// address registers

	string mnemonic;		// current instruction
	BitField ir;			// instruction register
	unsigned short pc;		// program counter
	
	bool negative;
	bool zero;
	bool running;

public:
	Processor();

	unsigned age( unsigned short address ) const;
	
	void reset();
	void run( unsigned short address );
	void step();

private:
	typedef void (Processor::*method)();

	short fetch();
	method decode();
	void setFlags( short );

	void exec_clr();
	void exec_move();

	void exec_add();
	void exec_sub();
	void exec_mul();
	void exec_div();

	void exec_and();
	void exec_or();
	void exec_eor();
	void exec_not();
	
	void exec_stop();
	
	void exec_undefined();

	friend class Reference;
	};

extern Processor g_cpu;

#endif
