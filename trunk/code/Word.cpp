
#include "Word.h"
#include "Timer.h"

Word* g_infoWord;

Word::Word( short v, Type t )
	: m_value(v), m_type(t), m_timestamp(g_timer.ticks())
	{ }

Word::~Word()
	{
	if ( g_infoWord == this )
		g_infoWord = NULL;		// clean up dangling pointer
	}

short Word::read() const
	{
	m_timestamp = g_timer.ticks();
	return m_value;
	}

void Word::write( short v )
	{
	m_timestamp = g_timer.ticks();
	m_value = v;
	}

Word::Type Word::type() const
	{ return m_type; }

void Word::touch()
	{ m_timestamp = g_timer.ticks(); }

short Word::peek() const
	{ return m_value; }

unsigned Word::age() const
	{ return g_timer.ticks() - m_timestamp; }
