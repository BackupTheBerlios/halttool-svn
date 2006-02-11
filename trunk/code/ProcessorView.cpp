
#include <cmath>

#include "ProcessorView.h"
#include "Color.h"
#include "graphics.h"

ProcessorView::ProcessorView( unsigned diameter )
	: CircleView( diameter )
	{ }

View* ProcessorView::click( point p )
	{
	parent->bringSubViewToFront( this );
	return this;
	}

void ProcessorView::drag( int dx, int dy )
	{
	bounds.x += dx;
	bounds.y += dy;
	glutPostRedisplay();
	}

void ProcessorView::draw()
	{
	glColor4f( 0.1, 0.1, 0.1, 0.8 );
	drawCircle( 0.99, outline );

	const float spaces = 10.0;
	const float circleRadius = 0.6 * M_PI / spaces;
	const float pathRadius = 0.9 - circleRadius;
	const float angleStep = 1.0 / spaces;

	float angle = 1.5 * angleStep;

	for ( unsigned reg = 0; reg <= 7; ++reg )
		{
		Color::palette["data"].set();

		gotoPoint( angle, pathRadius );
			drawCircle( circleRadius, outline );
		glPopMatrix();
		
		angle += angleStep;
		}
	}
