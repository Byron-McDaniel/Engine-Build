/*
Heartbeat headerfile; this is essentially heart of the engine.

4:12 PM - 9/18/17 - Byron - Changed update from a constant because the value DOES change.

*/

#ifndef _ENGINE_H
#define _ENGINE_H

//Declarations
enum SystemType;

class System;
class Game;

//C Runtime Header Files
#ifndef _WINDOWS_
#include <Windows.h>
#endif

#ifndef _map_
#include <map>
#endif

#ifndef _CONTEXT_H
#include "Context.h"
#endif


//Enumeration
enum EngineState
{
	Invalid,
	Constructing,
	Initializing,
	Running,
	ShuttingDown,
	Destroying

};

class Engine
{
public:
	Engine();
	~Engine();

	//void* operator new(size_t size);
	//void operator delete(void* pdelete);
	int RunLoop();

	static EngineState GetEngineState() { return m_EngineState; }

private:

	//private methods
	int Initialize();
	int Draw(Context& context);
	int Update(Context& context);
	int Shutdown();

	//Needs a core system
	int AddSystem(System* psys);
	//retrieve core system from engine
	template<typename T>
	T* GetSystem(SystemType systype)
	{
		T* psys = static_cast<T*>(m_mapSystems[systype]);
		if (!psys)
		{
			//Logger::Log("System was not valid.");
			return nullptr;
		}
	}

	//Create Instance of engine running
	Game* CreateGame();
	std::map<SystemType, System*> m_mapSystems;
	static EngineState m_EngineState;
};

#endif
