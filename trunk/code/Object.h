
#ifndef halt_Object
#define halt_Object

#include <string>
#include <map>

class Object
	{
protected:
	typedef void ( Object::*Method )( Object* sender );
	std::map< std::string, Method > methods; // for dynamic messages

public:
	Object();
	virtual ~Object();

	bool sendMessage( std::string message, Object* sender = NULL );
	};

#endif
