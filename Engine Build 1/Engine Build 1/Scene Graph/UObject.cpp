/*
This file is to initialize and manipulate objects.

*/

#include "UObject.h"

int UObject::m_ObjectAmount = 0;

UObject::UObject()
	:m_Name(_T(""))
	, m_ID(m_ObjectAmount)
	, m_bIsInitialized(false)
	, m_bIsPostInitialized(false)
	, m_bIsContentLoaded(false)
	, m_bIsPostContentLoaded(false)
	, m_bIsDestroyed(false)

	//By default the object can be drawn AND ticked.
	, m_bCanDraw(true)
	, m_bCanTick(true)
{
	m_Name = _T("Object") + TOSTRING(m_ID);
	++m_ObjectAmount;
}

UObject::UObject(const std::tstring& name)
	:m_Name(name)
	, m_ID(m_ObjectAmount)
	, m_bIsInitialized(false)
	, m_bIsPostInitialized(false)
	, m_bIsContentLoaded(false)
	, m_bIsPostContentLoaded(false)
	, m_bIsDestroyed(false)

	//By default the object can be drawn AND ticked.
	, m_bCanDraw(true)
	, m_bCanTick(true)
{
	++m_ObjectAmount;
}


UObject::~UObject()
{
}
