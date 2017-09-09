/*
Headerfile for WinMain.cpp this contains definitions, etc.

*/

#ifndef _WINMAIN_H //If WINMAIN is NOT defined
#define _WINMAIN_H //define this.


//Include the Windows header file if not already added.
#ifndef _WINDOW_
	#include <Windows.h>
#endif

int _tmain(int argc, char* argv[]); //Argument character, Argument Value

int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow); //DITTO

#endif //End the definition.