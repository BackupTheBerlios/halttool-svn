
#include "SystemView.h"
#include "Processor.h"
#include "Memory.h"
#include "Color.h"
#include "graphics.h"
#include "text.h"

#include <iomanip>
#include <sstream>
using namespace std;

SystemView::SystemView( unsigned diameter )
	: CircleView( diameter ), m_cpuScale( 0.4 )
	{ }

View* SystemView::click( point p )
	{
	// find the vector from the center to the clicked point
	float radius = bounds.w / 2.0;
	float x = ( p.x - radius ) / radius;
	float y = ( p.y - radius ) / radius;

	// vector magnitude
	float dist = sqrt( x*x + y*y );

	// normalize
	x /= dist;
	y /= dist;

	// determine the angle (in HALT coordinates)
	float angle = acos( -y );
	if ( x >= 0 )
		angle /= 2 * M_PI;
	else
		angle = ( M_PI - angle ) / ( 2 * M_PI ) + 0.5;

	// what was picked?
	if ( dist < m_cpuScale ) // inside the Processor area
		{
		if ( angle >= 0.1 && angle < 0.9 )
			{
			unsigned reg = static_cast< unsigned > ( angle * 10 ) - 1;

			ostringstream ss;
			ss << 'd' << reg;

			g_infoWord = &g_cpu.reg( reg );
			g_infoWordName = ss.str();
			}
		else
			{
			g_infoWord = NULL;
			g_infoWordName = "";
			}
		}
	else
		{
		const float memBegin = m_angleStep / 2;
		const float memEnd = memBegin + g_mem.size() / m_spaces;

		if ( angle >= memBegin && angle < memEnd )
			{
			unsigned short address = static_cast< unsigned short >
					((angle - memBegin) * m_spaces );

			ostringstream ss;
			ss << "(hex:" << hex << address << ")";

			g_infoWord = &g_mem.word( address );
			g_infoWordName = ss.str();
			}
		else
			{
			g_infoWord = NULL;
			g_infoWordName = "";
			}
		}

	glutPostRedisplay();
	return this;
	}

void SystemView::drag( int dx, int dy )
	{
	bounds.x += dx;
	bounds.y += dy;
	glutPostRedisplay();
	}

void SystemView::draw()
	{
	glColor4f( 0.1, 0.1, 0.1, 0.8 );
	drawCircle( 0.99, outline );

	// draw Memory
		{
		const unsigned memSize = g_mem.size();

		m_spaces = memSize + 4.0;
		m_circleRadius = 0.6 * M_PI / m_spaces;
		m_pathRadius = 0.9 - m_circleRadius;
		m_angleStep = 1.0 / m_spaces;

		float angle = m_angleStep;

		for ( unsigned addr = 0; addr < memSize; ++addr )
			{
			const Word& word = g_mem.word( addr );
			float intensity;

			switch ( word.age())
				{
				case 0: intensity = 1.0; break;
				case 1: intensity = 0.8; break;
				case 2: intensity = 0.6; break;
				case 3: intensity = 0.4; break;
				default: intensity = 0.2;
				}

			switch ( word.type() )
				{
				case Word::Data:
					Color::palette["data"].scaleValue( intensity ).set();
					break;
				case Word::Instruction:
					Color::palette["code"].scaleValue( intensity ).set();
					break;
				default:
					Color().set();
				}

			gotoPoint( angle, m_pathRadius );
				drawCircle( m_circleRadius, outline );
			glPopMatrix();
			
			angle += m_angleStep;
			}

		glLineWidth( 2.0 );

		// draw address registers
		for ( unsigned reg = 0; reg <= 7; ++reg )
			{
			unsigned short addr = g_cpu.addr( reg ).peek();
			if ( addr < memSize )
				{
				float intensity;
				switch ( g_cpu.addr( reg ).age())
					{
					case 0: intensity = 1.0; break;
					case 1: intensity = 0.8; break;
					case 2: intensity = 0.6; break;
					case 3: intensity = 0.4; break;
					default: intensity = 0.2;
					}
				Color::palette["address"].scaleValue( intensity ).set();

				gotoPoint( m_angleStep * ( addr + 1 ), m_pathRadius );
					drawCircle( 1.1 * m_circleRadius, stroke );
				glPopMatrix();
				}
			}

		Color().set(); // default color
		glPointSize( 3 );

		// unused address space
		drawPoint(( memSize + 1.0 ) / m_spaces, m_pathRadius );
		drawPoint(( memSize + 2.0 ) / m_spaces, m_pathRadius );
		drawPoint(( memSize + 3.0 ) / m_spaces, m_pathRadius );

		// begin / end boundary
		drawLine( 0, m_pathRadius - 0.1, m_pathRadius + 0.1 );
		glLineWidth( 1 ); // back to the default -- could push/pop
		}

	// draw Processor
		{
		glScalef( m_cpuScale, m_cpuScale, 1.0 );

		glColor4f( 0.1, 0.1, 0.1, 0.5 );
		drawCircle( 0.99, outline );

		const float spaces = 10.0;
		const float circleRadius = 0.6 * M_PI / spaces;
		const float pathRadius = 0.9 - circleRadius;
		const float angleStep = 1.0 / spaces;

		float angle = 1.5 * angleStep;

		// draw data registers
		for ( unsigned reg = 0; reg <= 7; ++reg )
			{
			float intensity;
			switch ( g_cpu.reg( reg ).age())
				{
				case 0: intensity = 1.0; break;
				case 1: intensity = 0.8; break;
				case 2: intensity = 0.6; break;
				case 3: intensity = 0.4; break;
				default: intensity = 0.2;
				}
			Color::palette["data"].scaleValue( intensity ).set();

			gotoPoint( angle, pathRadius );
				drawCircle( circleRadius, outline );
			glPopMatrix();
			
			angle += angleStep;
			}
		
		// use pixel coordinates
		endLocal();
		View::beginLocal();

		// draw status flags
		glColor4f( 1, 1, 1, ( g_cpu.negative() ? 0.75 : 0.25 ));
		drawText("N", point( bounds.w / 2 - fontWidth, (bounds.h - fontHeight) / 2 ));

		glColor4f( 1, 1, 1, ( g_cpu.zero() ? 0.75 : 0.25 ));
		drawText("Z", point( bounds.w / 2, (bounds.h - fontHeight) / 2 ));
		}
	}
