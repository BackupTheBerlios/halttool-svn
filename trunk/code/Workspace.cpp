
#include "Workspace.h"
#include "graphics.h"

Workspace::Workspace( size s )
	: View( s )
	{ }

void Workspace::draw()
	{
	beginLocal();
	
	glBegin( GL_QUADS );
		glColor3f( 0.8, 0.9, 1 );
		glVertex2i( 0, 0 );

		glColor3f( 0.7, 0.8, 1 );
		glVertex2i( bounds.w, 0 );

		glColor3f( 0.2, 0.3, 0.5 );
		glVertex2i( bounds.w, bounds.h );

		glColor3f( 0.1, 0.2, 0.4 );
		glVertex2i( 0, bounds.h );
	glEnd();

	endLocal();

	drawSubViews();
	}
