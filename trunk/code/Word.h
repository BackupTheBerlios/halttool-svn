
#ifndef halt_Word
#define halt_Word

#include <string>

class Word
	{
public:
	enum Type { Unknown, Data, Address, Instruction };

protected:	
	short m_value;
	Type m_type;
	mutable unsigned m_timestamp;

public:
	Word( short v = 0, Type t = Unknown );
	~Word();

	short read() const;
	void write( short );
	
	short peek() const;
	void touch();
	unsigned age() const;
	Type type() const;
	std::string typeString() const;
	};

extern const Word* g_infoWord;
extern std::string g_infoWordName;

#endif
