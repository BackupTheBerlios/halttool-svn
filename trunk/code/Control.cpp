
#include "Control.h"

using namespace std;

Control::Control( size s, string label )
	: View( s ),
	  target( NULL ), enabled( true ), m_label( label )
	{ }

Control::~Control()
	{ }
	
void Control::connect( Object* o, string message )
	{
	target = o;
	action = message;
	}

void Control::sendAction()
	{
//	if ( target == NULL or action.empty() )
//		;
//	else
//		target->sendMessage( action, this );
	
	if ( target and not action.empty() )
		target->sendMessage( action, this );
	}

bool Control::isEnabled()
	{ return enabled; }

void Control::setEnabled( bool newValue )
	{ enabled = newValue; }
