/*
String header file. This should be obvious. It adds a name to the object in the form of a string.

This file could be included in the UI file for an RPG, for instance.

*/

#ifndef _STRING_H
#define _STRING_H

//C Runtime Header Files
#ifndef _TCHAR_INC_
	#include <tchar.h>
#endif
#ifndef _STRING_
#include <string>
#endif



//Definitions
#ifdef UNICODE
	#define tstring wswring
	#define TOSTRING(value) std::to_wstring(value)
#else
	#define tstring string
	#define TOSTRING(value) std::to_string(value)
#endif

//Basically if the project uses Unicode, it will use the top set, otherwise it will use the bottom set for anything else. If the PROJECT uses unicode.
#endif //Defines the String Header.