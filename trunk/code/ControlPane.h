
#ifndef halt_ControlPane
#define halt_ControlPane

#include "Pane.h"
#include "Button.h"
#include "Timer.h"

class ControlPane : public Pane
	{
	enum Status { Idle, Running, Paused, Error };

	Status status;

	Button* resetButton;
	Button* runPauseButton;
	Button* stepButton;
//	Timer* timer;

public:
	ControlPane();
	
	void reset( Object* sender );
	void run( Object* sender );
	void pause( Object* sender );
	void step( Object* sender );
	};

#endif
