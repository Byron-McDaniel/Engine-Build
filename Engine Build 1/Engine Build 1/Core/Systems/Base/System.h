/*
Systems header file.

Note:File was created 6 months ago roughly, time & Date is unknown, it was before book keeping began.


10:25 AM - 9/3/17 - Byron - Changed public to protected methods.
*/

#ifndef _SYSTEM_H
#define _SYSTEM_H

//Additional files
#include "UObject.h"

#ifndef _CONTEXT_H
#include "Context.h"
#endif




//enumeration
enum SystemType
{
	Sys_Invalid,
	Sys_Window,
	Sys_Game,
	Sys_Input,
	Sys_Graphics,
	Sys_GameTimer,
	Sys_MAX
};

//Structures
struct SystemData
{
	SystemData();
	SystemData(const SystemType& type);

	SystemType systemType;
};

class System : public UObject
{
	friend class Engine;
public:
	SystemType GetType() { return m_SystemType; }

protected:
	System(const SystemData& data);
	virtual ~System();
	
	virtual bool Initialize() { return UObject::Initialize(); }
	virtual bool Update(Context& context) { return UObject::Update(context); }
	virtual bool ShutDown() { return UObject::ShutDown(); }

	SystemType m_SystemType;
};

#endif