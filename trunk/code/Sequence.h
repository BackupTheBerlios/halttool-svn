
#ifndef halt_Sequence
#define halt_Sequence

#include <string>
#include <vector>
#include <map>
#include <iostream>

#include "Object.h"
#include "Word.h"
#include "Token.h"
#include "EA.h"
#include "BitField.h"


class Sequence : public Object
	{
	// these are useful for the life of the sequence
	Word::Type m_type;
	std::string m_source;
	std::vector< Token > m_tokens;
	std::vector< short > m_code;
	std::vector< std::string > m_errors;

	struct CrossReference
		{
		std::string name;
		unsigned short offset;
		
		CrossReference( std::string n, unsigned short o )
			: name(n), offset(o)
			{ }
		};

	std::vector< CrossReference > m_crossRefs;

	// these are only used during construction
	std::vector< Token >::iterator token;
	BitField opWord;

	EA parseOperand();

	void asm_clr();
	void asm_move();
	void asm_lea();

	void asm_add_sub();
	void asm_mul_div();

	void asm_and_or();
	void asm_eor();
	void asm_not();

	void asm_branch();

public:
	Sequence( std::string sourceText );

	void translate();
	bool success() const;

	Word::Type type() const;

	const std::string name() const;
	const std::string& source() const;
	const std::vector< Token >& tokens() const;
	const std::vector< short >& code() const;

	void bind( const std::map< std::string, unsigned short >& symbols );
	void dump( std::ostream& ) const;
	};

#endif
