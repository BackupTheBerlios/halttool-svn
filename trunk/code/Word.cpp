
#include "Word.h"
#include "Clock.h"

Word::Word( short v, Type t )
	: m_value(v), m_type(t), m_timestamp(g_clock.time())
	{ }

short Word::read() const
	{
	m_timestamp = g_clock.time();
	return m_value;
	}

void Word::write( short v )
	{
	m_timestamp = g_clock.time();
	m_value = v;
	}

Word::Type Word::type() const
	{ return m_type; }

void Word::touch()
	{ m_timestamp = g_clock.time(); }

short Word::peek() const
	{ return m_value; }

unsigned Word::age() const
	{ return g_clock.time() - m_timestamp; }
