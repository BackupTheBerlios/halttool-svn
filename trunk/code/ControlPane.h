
#ifndef halt_ControlPane
#define halt_ControlPane

#include "Pane.h"
#include "Button.h"

class ControlPane : public Pane
	{
	Button* resetButton;
	Button* runPauseButton;
	Button* stepButton;
public:
	ControlPane();
	};

#endif
