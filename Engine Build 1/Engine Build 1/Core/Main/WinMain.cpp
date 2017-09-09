/*
This contains the initialization of the engine script. 

*/

#include "WinMain.h"
//Additional Include files.
#ifndef _STRING_H //You need strings.
#include "string.h"
#endif

#ifndef _IOSTREAM_H //not sure what IOSTREAM does.
	#include "iostream.h"
#endif

#ifndef _DELETEMACRO_H
#include "DeleteMacros.h"
#endif

//Functions.
#if defined (DEBUG) | defined(_DEBUG)
int _tmain(int argc, char* argv[]) //Argument Character, Argument Value
{
	//not using these. Yet.
	UNREFERENCED_PARAMETER(argc);
	UNREFERENCED_PARAMETER(argv);

	//Logger:Log("Starting the program");
	//Run WinMain Function
	WinMain((HINSTANCE)GetModuleHandle(NULL), 0, 0, SW_SHOW);
}
#endif

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	//not using these. Yet.
	UNREFERENCED_PARAMETER(hInstance);
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);
	UNREFERENCED_PARAMETER(nCmdShow);



//Catch Memory leaks.
#if defined (DEBUG) | defined(_DEBUG)
	HeapSetInformation(NULL, HeapEnableTerminationOnCorruption, NULL, 0);

	//Enable Runtime-memory leak checker...
	//_CrtlSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	//CtrlSetBreakAlloc(0);

#endif

	//Create the engine
	//Engine* pEngine = new Engine();

	//Give the game a kick in the ass to get it running.
	//int result = pEngine->RunLoop();

	//Take it out back and kill it.
	//SafeDelete(pEngine);

	//return result;

	return 0;
}