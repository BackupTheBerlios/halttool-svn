
#ifndef halt_Timer
#define halt_Timer

#include <vector>

#include "Control.h"

class Timer : public Control
	{
	static std::vector<Timer*> timers;
	static void trigger( int );

	const unsigned timerID;
	unsigned m_delay;
	unsigned m_ticks;

public:
	Timer( float hertz );

	float rate();
	void rate( float hertz );

	void reset();
	void start();
	void stop();

	unsigned ticks();

//----------------	
	void draw();
	};

extern Timer g_timer;

#endif
