/*
Header file for Game.cpp. This'll be what the particular game'll be when I get to it.

*/

#ifndef _GAME_H
#define _GAME_H

#include "System.h"

//Structures
struct GameData : public SystemData
{

};

class Game : public System
{
public:
	Game(const GameData&  Data);
	~Game();


};
#endif