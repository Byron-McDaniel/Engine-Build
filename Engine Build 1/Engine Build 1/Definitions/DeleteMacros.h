/*
This header file deletes macros.

*/

#ifndef _DELETEMACRO_H
#define _DELETEMACRO_H

//Defines
#pragma region Definitions
#define SafeRelease(x) if(x) {x -> Release(); x = nullptr}; //Macro for releasing COM Objects

#define SafeDelete(x) if (x){delete x; x = nullptr;} //Macro is deleted.

#endif

#pragma endregion