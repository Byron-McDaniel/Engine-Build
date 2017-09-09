/*
Header for Window class.


10:13 AM - 9/3/17 - Byron - Header created.

*/

#ifndef _WINDOW_H
#define _WINDOW_H



#include "System.h"

//Additional C runtime files
#ifndef _WINDOWS_
#include <Windows.h>
#endif

//Additional Includes
#ifndef _CONTEXT_H
#include "Context.h"
#endif

#ifndef _STRING_H
#include "string.h"
#endif

struct WindowData : public SystemData
{
	WindowData();
	WindowData(int w, int h, const std::tstring& title = _T("Engine Build v 0.01 PRE-ALPHA"), int b = 32, bool fs = false);

	int width, height, bits;
	std::tstring windowTitle;
	bool fullscreen;

};

struct ResizeData
{
	ResizeData();
	ResizeData(bool resize, int nw, int nh);

	bool MustResize;
	int newWidth, newHeight;

};

class Window :	public System
{

	friend class Engine;
public:
	int GetWidth(), GetHeight();

	HWND GetWindowHandle();
	HDC GetDeviceContext();
	HINSTANCE GetInstance();

	ResizeData& GetResizeData() { return m_ResizeData; }

	LRESULT HandleEvent(HWND HWnd, UINT msg, WPARAM wParam, LPARAM lParam);


protected:
	Window(const WindowData& data);
	~Window();

	virtual bool Initialize();
	virtual bool Update(Context& context);
	virtual bool ShutDown();

private:

	bool CenterWindow();

	//sub members
	HWND m_hWindow;
	HDC m_hDC;
	HINSTANCE m_Inst;
	int m_Width, m_Height, m_Bits;
	bool m_bFullscreen;

	std::tstring m_Title;
};

#endif