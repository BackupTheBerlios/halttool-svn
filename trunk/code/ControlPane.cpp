
#include "ControlPane.h"
#include "Indicator.h"

ControlPane::ControlPane()
	: Pane( size( 220, 40 )),
	  resetButton( new Button( size( 50, 20 ),"Reset")),
	  runPauseButton( new Button( size( 50, 20 ),"Run")),
	  stepButton( new Button( size( 50, 20 ),"Step"))
	{
	addSubView( resetButton, point( 10, 10 ));
	addSubView( runPauseButton, point( 70, 10 ));
	addSubView( stepButton, point( 130, 10 ));
	addSubView( new Indicator( 20 ), point( 190, 10 ));
	}
