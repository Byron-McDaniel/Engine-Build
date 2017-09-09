/*
This file is to initialize and manipulate objects.

*/

#ifndef _UOBJECT_H
#define _UOBJECT_H

//Include files.
#ifndef _CONTEXT_H
#include "context.h"
#endif

#ifndef _STRING_H
#include "string.h"
#endif

class UObject
{
public:
	UObject();
	UObject(const std::tstring& name);
	virtual ~UObject();
	/*
	Not quite ready yet.
	void * operator new(size_t size);
	void operator delete(void* pdelete);
	*/

	virtual bool Initialize() { m_bIsInitialized = true; return true; }
	virtual bool PostInitialize() { m_bIsPostInitialized = true; return true; }
	virtual bool LoadContent() { m_bIsContentLoaded = true; return true; }
	virtual bool PostLoadUpdate() { m_bIsPostContentLoaded = true; return true; }
	virtual bool Update(Context& context) { return true; }
	//virtual bool LateUpdate(Context& context) { return true; }
	virtual bool Draw(Context& context) { return true; }
	virtual bool DrawUI(Context& context) { return true; }
	virtual bool ShutDown() { return true; }

	void SetName(const std::tstring& name) { m_Name = name; }
	const std::tstring& GetName() { return m_Name; }
	
	void Activate() { m_bIsActivated = true; }
	void Deactivate() { m_bIsActivated = false; }
	bool IsActivate() { return m_bIsActivated; }
	
	bool IsInitialized() const { return m_bIsInitialized;  }
	bool IsPostInitialized() const { return m_bIsPostInitialized;  }
	bool IsContentLoaded() const { return m_bIsContentLoaded; }
	bool IsPostContentLoaded() const { return m_bIsPostContentLoaded; }

	void SetCanTick(bool canTick) { m_bCanTick = canTick;  }
	bool CanTick() const { return m_bCanTick; }
	void SetCanDraw(bool canDraw) { m_bCanDraw = canDraw; }
	bool CanDraw() const { return m_bCanDraw; }
	void Destroy() { m_bIsDestroyed = true; }
	bool IsDestroyed() { return m_bIsDestroyed; }

protected:
	//content id?
	static int m_ObjectAmount;
	int m_ID;

	bool m_bIsActivated;
	bool m_bIsInitialized;
	bool m_bIsPostInitialized;
	bool m_bIsContentLoaded;
	bool m_bIsPostContentLoaded;

	std::tstring m_Name;

private:
	bool m_bIsDestroyed;
	bool m_bCanTick;
	bool m_bCanDraw;
};
#endif
