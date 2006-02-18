
#include "ControlPane.h"
#include "Processor.h"
#include "graphics.h"

ControlPane::ControlPane()
	: Pane( size()),
	  resetButton( new Button("Reset")),
	  runPauseButton( new Button("Pause")),
	  stepButton( new Button("Step"))
//	  timer( new Timer( 5.0 ))
	{
	addSubView( &g_timer, point( 10, 10 ));

	addSubView( resetButton,
		point( g_timer.getPosition().x + g_timer.getSize().w + 10, 10 ));

	addSubView( runPauseButton,
		point( resetButton->getPosition().x + resetButton->getSize().w + 10, 10 ));

	addSubView( stepButton,
		point( runPauseButton->getPosition().x + runPauseButton->getSize().w + 10, 10 ));

	rect r = stepButton->boundsRect();

	setSize( size( r.x + r.w + 10, r.h + 20 ));

	methods["reset"] = (Method) &ControlPane::reset;
	methods["run"] =   (Method) &ControlPane::run;
	methods["pause"] = (Method) &ControlPane::pause;
	methods["step"] = (Method) &ControlPane::step;
	
	resetButton->connect( this,"reset");
	stepButton->connect( this,"step");
	g_timer.connect( this,"step");

	reset( this );
	}

void ControlPane::reset( Object* sender )
	{
	status = Idle;
	runPauseButton->label("Run");
	runPauseButton->connect( this,"run");

	g_timer.stop();
	g_timer.rate( 10.0 ); // hertz

	g_cpu.reset();
	}

void ControlPane::run( Object* sender )
	{
	status = Running;
	runPauseButton->label("Pause");
	runPauseButton->connect( this,"pause");

	g_cpu.start();
	g_timer.start();
	}

void ControlPane::pause( Object* sender )
	{
	status = Paused;
	runPauseButton->label("Run");
	runPauseButton->connect( this,"run");

	g_timer.stop();
	}

void ControlPane::step( Object* sender )
	{
	g_cpu.step();

	if ( not g_cpu.running())
		g_timer.stop();

	glutPostRedisplay();
	}
