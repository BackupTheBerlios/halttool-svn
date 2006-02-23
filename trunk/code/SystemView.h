
#ifndef halt_SystemView
#define halt_SystemView

#include "CircleView.h"

class SystemView : public CircleView
	{
	float m_cpuScale;

public:
	SystemView( unsigned diameter );
	
	View* click( point );
	void drag( int dx, int dy );

	void draw();
	};

#endif
