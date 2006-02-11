
#include <cstdlib>
#include <cmath>

#include "MemoryView.h"
#include "Color.h"
#include "graphics.h"

using namespace std;

MemoryView::MemoryView( unsigned diameter )
	: CircleView( diameter )
	{ }

View* MemoryView::click( point p )
	{
	parent->bringSubViewToFront( this );
	return this;
	}

void MemoryView::drag( int dx, int dy )
	{
	bounds.x += dx;
	bounds.y += dy;
	glutPostRedisplay();
	}

void MemoryView::draw()
	{
	glColor4f( 0.1, 0.1, 0.1, 0.8 );
	drawCircle( 0.99, outline );

	const unsigned memSize = g_mem.size();
	const float spaces = memSize + 4.0;
	const float circleRadius = 0.6 * M_PI / spaces;
	const float pathRadius = 0.9 - circleRadius;
	const float angleStep = 1.0 / spaces;

	float angle = angleStep;

	for ( unsigned addr = 0; addr < memSize; ++addr )
		{
		const Word& word = g_mem.peek( addr );

		switch ( word.type() )
			{
			case Word::Data:
				Color::palette["data"].set();
				break;
			case Word::Instruction:
				Color::palette["code"].set();
				break;
			default:
				Color().set();
			}

		gotoPoint( angle, pathRadius );
			drawCircle( circleRadius, outline );
		glPopMatrix();
		
		angle += angleStep;
		}

	Color().set(); // default color
	glPointSize( 3 );

	// unused address space
	drawPoint(( memSize + 1.0 ) / spaces, pathRadius );
	drawPoint(( memSize + 2.0 ) / spaces, pathRadius );
	drawPoint(( memSize + 3.0 ) / spaces, pathRadius );

	// begin / end boundary
	glLineWidth( 2 );
	drawLine( 0, pathRadius - 0.1, pathRadius + 0.1 );
	glLineWidth( 1 ); // back to the default -- could push/pop
	}
