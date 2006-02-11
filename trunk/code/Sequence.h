
#ifndef halt_Sequence
#define halt_Sequence

#include <string>
#include <vector>
#include <iostream>

#include "Word.h"
#include "Token.h"
#include "EA.h"

class Sequence
	{
protected:
	Word::Type m_type;
	std::string m_source;
	std::vector< Token > m_tokens;
	std::vector< short > m_code;
	std::vector< std::string > m_errors;

	EA parseOperand( std::vector< Token >::iterator& );

public:
	Sequence( std::string sourceText );

	void translate();
	bool success() const;

	Word::Type type() const;

	const std::string& source() const;
	const std::vector< Token >& tokens() const;
	const std::vector< short >& code() const;

	void dump( std::ostream& ) const;
	};

#endif
