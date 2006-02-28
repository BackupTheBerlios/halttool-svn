
#include "WordInspector.h"
#include "Word.h"
#include "graphics.h"
#include "text.h"

#include <sstream>
#include <iomanip>

using namespace std;

WordInspector::WordInspector()
	: Pane( size( 2*margin + 20*fontWidth, 2*margin + 6*fontHeight + 5*leading ))
	{ }

void WordInspector::draw()
	{
	glColor4f( 0.1, 0.1, 0.1, 0.8 );
	localRect().fill();

	// draw dividers
	glColor4f( 0, 0, 0, 0.5 );
	glBegin( GL_LINES );
		{
		// horizontal divider
		unsigned y = margin + fontHeight + fontHeight / 2 + leading;
		glVertex2i( 0, y );
		glVertex2i( bounds.w, y );

		// vertical divider
		unsigned x = margin + 8 * fontWidth;
		glVertex2i( x, y );
		glVertex2i( x, bounds.h );
		}
	glEnd();

	// draw field labels
	glColor4f( 1, 1, 1, 0.5 );
	drawText("Word Inspector", 1 );
	drawText("address", 3 );
	drawText("   type", 4 );
	drawText("  value", 5 );

	// draw field values
	if ( g_infoWord )
		{
		ostringstream decValue, hexValue;
		decValue << g_infoWord->peek();
		hexValue << "hex:" << hex << g_infoWord->peek();

		glColor3f( 1, 1, 1 );
		drawText( g_infoWordName, 3, 9 );
		drawText( g_infoWord->typeString(), 4, 9 );
		drawText( decValue.str(), 5, 9 );
		drawText( hexValue.str(), 6, 9 );
		}

	glColor3f( 0, 0, 0 );
	localRect().stroke();
	}
