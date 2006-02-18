
#include "Timer.h"
#include "Color.h"
#include "graphics.h"
#include "utility.h"
#include <iostream>
std::vector<Timer*> Timer::timers;
Timer g_timer(1.0);

Timer::Timer( float hertz )
	: Control( size( 10, 10 )), timerID( timers.size()), m_ticks( 0 )
	{
	timers.push_back( this );
	rate( hertz );
	
	std::cerr <<"Timer: "<< timerID <<' '<< timers.size() <<' '<< m_delay << std::endl;
	}

float Timer::rate()
	{
	return 1000.0 / m_delay;
	}

void Timer::rate( float hertz )
	{
	clamp<float>( hertz, 1.0, 1000.0 );
	m_delay = static_cast <unsigned> ( 1000.0 / hertz );
	}

unsigned Timer::ticks()
	{ return m_ticks; }

void Timer::reset()
	{
	enabled( false );
	m_ticks = 0;
	}

void Timer::start()
	{
	enabled( true );
	glutTimerFunc( 0, Timer::trigger, timerID );
	}

void Timer::stop()
	{
	enabled( false );
	}

void Timer::trigger( int id )
	{
	Timer& timer = *(timers[id]);
	if ( timer.enabled())
		{
		timer.sendAction();
		++timer.m_ticks;
		glutTimerFunc( timer.m_delay, Timer::trigger, id );
		}
	}

void Timer::draw()
	{
	Color(0.333).scaleValue( m_ticks & 1 ? 0.6 : 0.4 ).set();
	localRect().fill();

	glColor3f( 0, 0, 0 );
	localRect().stroke();
	}