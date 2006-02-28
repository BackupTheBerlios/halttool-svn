
#ifndef halt_Processor
#define halt_Processor

// A simple 16-bit processor

#include <string>

#include "Object.h"
#include "BitField.h"
#include "Memory.h"

class Processor : public Object
	{
	Memory regs;			// data registers
	unsigned short a[8];	// address registers

	std::string mnemonic;	// current instruction
	BitField ir;			// instruction register
	BitField sr;			// status register
	unsigned short pc;		// program counter
	

	bool m_error;
	bool m_running;

public:
	Processor();

	// data registers
	const Word& reg( unsigned short address ) const;

	// status flags
	bool negative() const;
	bool zero() const;
	
	void reset();
	void step();

	bool smoothSailing();

private:
	short fetch();
	Method decode();
	void setFlags( short );

	void exec_clr();
	void exec_move();
	void exec_lea();

	void exec_add();
	void exec_sub();
	void exec_mul();
	void exec_div();

	void exec_and();
	void exec_or();
	void exec_eor();
	void exec_not();
	
	void exec_nop();
	void exec_stop();
	
	void exec_undefined();

	friend class Reference;
	};

extern Processor g_cpu;

#endif
