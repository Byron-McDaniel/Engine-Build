/*
This file is the same as the String header file, but it handles unicode, which is for foreign languages or for symbols.

*/

#ifndef _IOSTREAM_H
#define _IOSTREAM_H

//C Runtime Header includes
#ifndef _IOSTREAM_
	#include <iostream>
#endif

//Definitions again.
#ifdef UNICODE
	#define tcout wcout
	#define tcin wcin
#else
	#define tcout cout
	#define tcin cin
#endif


//Does exactly what the string header does. If it uses unicode, it uses the first set, if not it uses the secondary set. If the PROJECT uses Unicode.

#endif //_IOSTREAM header

//KILL ALL HUMANS