
#ifndef halt_graphics
#define halt_graphics

	#ifdef __APPLE__
		// Mac OS X
		#include <GLUT/glut.h>
	#else
		// Linux or Windows
		#include <GL/glut.h>
	#endif

#endif
