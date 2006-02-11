
#include <iostream>

#include "Object.h"

using namespace std;

Object::Object()
	{ }

Object::~Object()
	{ }

bool Object::sendMessage( string message, Object* sender )
	{
	map< string, Method >::iterator found = methods.find( message );

	if ( found != methods.end() )
		{
		Method action = found->second;
		(*this.*action)( sender );
		return true;
		}
	else
		{
		clog << "huh?" << endl;
		return false;
		}
	}
