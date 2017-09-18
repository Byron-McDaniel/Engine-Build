/*
This is the context file which will likely contain several conditions.

7:30 PM - 9/9/17 - Byron - Added a pWnd variable to use in the Window.CPP class.
2:00 PM - 9/18/2017 - Byron - Continue adding functions.
*/

#ifndef _CONTEXT_H
#define _CONTEXT_H

//Forward Declarations.
class Window;

//Definitions.
#define WINDOW (context.pWnd)


struct Context
{
	float dTime;

	Window* pWnd;
};

#endif