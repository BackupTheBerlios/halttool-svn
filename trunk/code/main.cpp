#include <ctime>
#include <iostream>

using namespace std;

#include "graphics.h"
#include "Workspace.h"
#include "ProgramEditor.h"
#include "MemoryView.h"
#include "ProcessorView.h"
#include "Color.h"
#include "Clock.h"
#include "Indicator.h"

#include "ControlPane.h"

// globals -----------------------------------------

Workspace* screen;

View* mouseTarget;	// drag, release go to View that received initial click
View* keyTarget;

bool dragging = false;
point dragOrigin;

// setup OpenGL ----------------------------------------

void initGL()
	{
	glShadeModel( GL_SMOOTH );

	glEnable( GL_SCISSOR_TEST );

	glEnable( GL_BLEND );
	glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
	}

// GLUT callbacks ------------------------------------------

void keyboard( unsigned char key, int x, int y )
	{
	if ( keyTarget )
		{
		switch ( key )
			{
			case 0x03:	key = enterKey;			break;
			case 0x0d:	key = returnKey;		break;
		#ifdef __APPLE__
			case 0x08:	key = deleteKey;		break;
			case 0x7f:	key = backspaceKey;		break;
		#else
			case 0x7f:	key = deleteKey;		break;
			case 0x08:	key = backspaceKey;		break;
		#endif
			}

		keyTarget->key( key );
		}
	}

void special( int rawKey, int x, int y )
	{
	if ( keyTarget )
		{
		char key = nullKey;

		switch ( rawKey )
			{
			case GLUT_KEY_LEFT:		key = leftKey;		break;
			case GLUT_KEY_RIGHT:	key = rightKey;		break;
			case GLUT_KEY_UP:		key = upKey;		break;
			case GLUT_KEY_DOWN:		key = downKey;		break;
			case GLUT_KEY_HOME:		key = homeKey;		break;
			case GLUT_KEY_END:		key = endKey;		break;
			}

		keyTarget->key( key );
		}
	}

void mouse( int Button, int state, int x, int y )
	{
	if ( state == GLUT_DOWN )
		{
		mouseTarget = screen->click( point( x, y ));

		if ( mouseTarget->acceptsKey())
			keyTarget = mouseTarget;

		dragOrigin = point( x, y );
		dragging = true;
		}
	else
		{
		mouseTarget->release();
		dragging = false;
		}
	}

void motion( int x, int y )
	{
	if ( dragging )
		{
		mouseTarget->drag( x - dragOrigin.x, y - dragOrigin.y );
		dragOrigin = point( x, y );
		}
	}

void reshape( int w, int h )
	{ screen->setSize( size( w, h )); }

void display()
	{
	screen->draw();
	glutSwapBuffers();
	}

void timer( int ms )
	{
	g_clock.tick();
	glutTimerFunc( ms, timer, ms );
	glutPostRedisplay();
	}

// --------------------------------------------------

int main( int argc, char* argv[] )
	{
	Color::palette["error"] = Color( 0 );
	Color::palette["command"] = Color( 0.8 );
	Color::palette["code"] = Color( 0.333 );
	Color::palette["data"] = Color( 0.6 );
	Color::palette["address"] = Color( 0.1 );

	// create the interface ------------------------------

	screen = new Workspace;
	mouseTarget = screen;
	size screenSize( 500, 500 );

	screen->addSubView( new MemoryView( 300 ), point( 50, 50 ));
	screen->addSubView( new ProcessorView( 128 ), point( 200, 50 ));

	ProgramEditor* progEdit = new ProgramEditor;
	progEdit->program( new Program );
	screen->addSubView( progEdit, point( 10, 100 ));

	screen->addSubView( new ControlPane, point( 2, 2 ));

	// roll the dice

	srand( time( 0 ));

	// setup GLUT ------------------------------------------

	glutInit( &argc, argv );
	glutInitDisplayMode( GLUT_RGB | GLUT_DOUBLE );

	glutInitWindowSize( screenSize.w, screenSize.h );
	glutCreateWindow("Humane Assembly Language Tools");
//	glutFullScreen();

	glutDisplayFunc( display );
	glutReshapeFunc( reshape );
	glutKeyboardFunc( keyboard );
	glutSpecialFunc( special );
	glutMouseFunc( mouse );
	glutMotionFunc( motion );

	initGL();

	glutTimerFunc( 1000, timer, 100 );

	glutMainLoop();
	}
