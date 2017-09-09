/*
This is the heartbeat class. This is essentially the heart of the engine. After initialization, it will display the render and all that jazz.

*/

#include "Engine.h"

//added include files.
#include "System.h"
#include "Game.h"

#ifndef _DELETEMACRO_H
#include "DeleteMacros.h"
#endif

#ifndef _STRING_H
#include "string.h"
#endif



EngineState Engine::m_EngineState = EngineState::Invalid;


Engine::Engine()
{
	m_EngineState = EngineState::Constructing;
}

Engine::~Engine()
{
	m_EngineState = EngineState::Destroying; 
}


//public
#pragma region Public Methods

int Engine::RunLoop()
{

	Context context;
	if (!this->Initialize())
		return 0;

	srand(GetTickCount());

	MSG msg = {};

	m_EngineState = EngineState::Running;

	while (msg.message != WM_QUIT && m_EngineState == EngineState::Running)
	{
		//CheckResize();
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		this->Update(context);
		this->Draw(context);
	}

	//Logger::Log("Ending the program");
	//Logger::WriteLogFile();

	if (!this->Shutdown())
		return 0;
	return msg.wParam;
}

#pragma endregion

//Private
#pragma region Private Methods
int Engine::Initialize()
{
	m_EngineState = EngineState::Initializing;

	Game* game = CreateGame();

	if (!game)
	{
		return false;
	}

	//add systems (none quite yet)


	return true;
}

int Engine::Draw(const Context& context)
{
	return true;
}
int Engine::Update(const Context& context)
{
	return true;
}

int Engine::Shutdown()
{
	m_EngineState = EngineState::ShuttingDown;

	//delete the systems
	for (std::pair<SystemType, System*>psys : m_mapSystems)
	{
		/*if (!psys.second->ShutDown())
		{
			//Log::Logger("I SHOT MYSELF IN THE FOOT! The system didn't shut down properly: " + psys->GetSystemType();
		}
		*/

		SafeDelete(psys.second);

	}

	return true;
}

int Engine::AddSystem(System* psys)
{
	auto element = m_mapSystems.insert(std::make_pair(psys->GetType(), psys));
	if (element.second)
	{
		return true;
	}
	else
	{
	return false;
	}
}

Game* Engine::CreateGame()
{
	if (!AddSystem(new Game(GameData())))
		return nullptr;
	
	Game* game = GetSystem<Game>(SystemType::Sys_Game);
	/*if (!game->Initialize())
		return nullptr;
	*/		
	return game;
}
#pragma endregion