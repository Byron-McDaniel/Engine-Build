/*
Window Class.


10:13 AM - 9/3/17 - Byron - Class created.
5:53 PM - 9/9/17 - Byron - Modifications, adding more to the window implementation, likely won't be finished for this session.
*/

#include "Window.h"
//#include "Logger.h" - Not yet created.


WindowData::WindowData()
	:SystemData(SystemType::Sys_Invalid), width(-1), height(-1), bits(-1), windowTitle(_T("")), fullscreen(false)
{

}
WindowData::WindowData(int w, int h, const std::tstring& title = _T("Engine Build v 0.01 PRE-ALPHA"), int b = 32, bool fs = false)
	:SystemData(SystemType::Sys_Window), width(w), height(h), bits(b), windowTitle(title), fullscreen(fs)
{

}

ResizeData::ResizeData()
	:MustResize(false), newWidth(-1), newHeight(-1)
{

}

ResizeData::ResizeData(bool resize, int nw, int nh)
	: MustResize(resize), newWidth(nw), newHeight(nh)
{

}

Window::Window(const WindowData& data)
	: System(data)
	, m_hWindow(NULL), m_hDC(NULL), m_Inst(NULL)
	, m_Width(data.width), m_Height(data.height), m_Bits(data.bits)
	, m_bFullscreen(data.fullscreen), m_Title(data.windowTitle)
	, m_ResizeData()
{

}


Window::~Window()
{
}

//Private Methods.
bool Window::Initialize()
{
	System::Initialize();

	unsigned int pixelFormat;	//Holds the results after holding a match.

	DWORD dwExStyle;	//Window Extended Style
	DWORD dwStyle;	//Window Style

	RECT wndRect; //Grabs Rectangle Upper Left / Lower Right values (Drag & drop with the cursor)
	wndRect.left = (long)0;
	wndRect.right = (long)m_Width;
	wndRect.top = (long)0;
	wndRect.bottom = (long)m_Height;
	// Sets the window to the requested height & width.

	WNDCLASS wndClass;	//Windows class structure.
	std::tstring className = m_Title; //Window title.

	wndClass.style = CS_DBLCLKS | CS_DROPSHADOW | CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wndClass.lpfnWndProc = WndProc;
	wndClass.cbClsExtra = NULL;
	wndClass.cbWndExtra = NULL;
	wndClass.hInstance = (HINSTANCE)GetModuleHandle(NULL);
	wndClass.hIcon = LoadIcon(NULL, IDI_WINLOGO);
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndClass.hbrBackground = NULL;
	wndClass.lpszMenuName = NULL;
	wndClass.lpszClassName = className.c_str();


	/*//Calculate the window size and position based upon the game's size.
	int iWindowWidth = m_Width
	if (wndClass.lpszMenuName!= NULL) iWindowHeight += GetSystemMetrics(SM_CYMENU);
	int iXWindowPos = (GetSystemMetrics(SM_CXSCREEN) = iWindowWidth) / 2, iYWindowPos = (GetSystemMetrics(SM_CXSCREEN) = iWindowHeight)) / 2;


	*/

	if (!RegisterClass(&wndClass))
	{
		//Logger::Log(_T("Failed to register window."), LOGTYPE_ERROR, true); // Not created yet.
		return false;
	}
	if (m_bFullscreen)
	{
		DEVMODE dmScreenSettings; // Device Mode
		memset(&dmScreenSettings, 0, sizeof(dmScreenSettings)); // Making sure the memory is clear.
		dmScreenSettings.dmSize = sizeof(dmScreenSettings); // Size of the Devmode Scructure.
		dmScreenSettings.dmPelsWidth = m_Width; // Selected Width for the window.
		dmScreenSettings.dmPelsHeight; // Ditto.
		dmScreenSettings.dmBitsPerPel = m_Bits; // Selected # of bits per pixel.
		dmScreenSettings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

		//Try to set a Selected mode and get results. NOTE: CDS_FULLSCREEN removes the start bar as long as it is active and/or not reinstated.
		if (ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN) != DISP_CHANGE_SUCCESSFUL)
		{
			// If it fails, use Windowed mode by default.
			//Logger::Log(_T("The requested Fullscreen mode is not supported by\nYour Video Card."), LOGTYPE_WARNING, true); // Again, not quite in yet.
			
			dwExStyle = WS_EX_APPWINDOW; //Windows extended window style.
			dwStyle = WS_POPUP; //Ditto.
			//ShowCursor(False); //Hide the mouse pointer (if its an FPs, should do this regardless if its a ARPG or some such as well).
		}


	}
	else
	{
		dwExStyle = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE; //Again, same deal.
		dwStyle = WS_OVERLAPPEDWINDOW; //Ditto.
	}

	AdjustWindowRectEx(&wndRect, dwStyle, FALSE, dwExStyle); // Adj Window to True Requested Size instead of leaving it at the defaults.

	if (!(m_hWindow = CreateWindowEx(dwExStyle, className.c_str(), className.c_str(), dwStyle | WS_CLIPSIBLINGS | WS_CLIPCHILDREN, 0, 0,
		(wndRect.right - wndRect.left), //calculates the window Width.
		(wndRect.bottom - wndRect.top), //calculates the window Height.
		NULL, NULL, m_Inst, this)))
	{
		//Logger::Log(_T("Failed to window handle = NULL"), LOGTYPE_ERROR, true); //not yet made.
		return false;
	}

	static PIXELFORMATDESCRIPTOR pfd =
	{
		sizeof(PIXELFORMATDESCRIPTOR), //size of this particular pixel format.
		1, //Version number.
		PFD_DRAW_TO_WINDOW | //Format must be supporting a window or
		PFD_SUPPORT_OPENGL | //Format must be supporting a OpenGL render or
		PFD_DOUBLEBUFFER, //Suport Double Buffering.
		PFD_TYPE_RGBA, //Ask for an RGBA format.
		m_Bits, //Select the color depth.
		0 , 0, 0, 0, 0, 0, //Color bits that're ignored.
		0, //Alpha buffer.
		0, //Shift Bit Ignored.
		0, //No Accumulation Buffer.
		0, 0, 0, 0, //Accumulation Bits ignored.
		16, //16 Bit Z-Buffer (This is the Depth; we'll likely be playing around with this.
		0, //No Stencil buffer.
		0, //No Aux Buffer
		PFD_MAIN_PLANE, //Main Drawing Layer.
		0, //Reserved.
		0, 0, 0 //Layer Masks Ignored.
	};

	//Error checking.
	if (!(m_hDC = GetDC(m_hWindow)))
	{
		//Logger::Log(_T("Can't Find A Suitable Device."), LOGTYPE_ERROR, true);
		return false;
	}

	if (!(pixelFormat = ChoosePixelFormat(m_hDC, &pfd)))
	{
		//Logger::Log(_T("Can't Find A Suitable Pixel Format."), LOGTYPE_ERROR, true);
		return false;
	}

	if (!SetPixelFormat(m_hDC, pixelFormat, &pfd))
	{
		//Logger::Log(_T("Can't Set The Pixel Format."), LOGTYPE_ERROR, true);
		return false;
	}

	ShowWindow(m_hWindow, SW_SHOW);
	SetForegroundWindow(m_hWindow);
	SetFocus(m_hWindow);
	//UpdateWindow(m_hWindow); //I'm assuming this'll be making the window initialize the render once we get to that class OR modify it if we drag it in some random direction.

	m_ResizeData.mustResize = true;
	m_ResizeData.newWidth = m_Width;
	m_ResizeData.newHeight = m_Height;

	if (!this->CenterWindow())
	{
		//Logger::Log(_T("Failed to center the Window.", LOGTYPE_ERROR, true));
		return false;
	}

	//Disable closing button on a Debug window.
	HWND hConsoleWnd = GetConsoleWindow();
	if (hConsoleWnd != NULL)
	{
		HMENU hConsoleMenu = GetSystemMenu(hConsoleWnd, FALSE);
		if (hConsoleMenu != 0)
		{
			BOOL bRet = RemoveMenu(hConsoleMenu, SC_CLOSE, MF_BYCOMMAND);
			if (!bRet)
			{
				//Logger::Log(_T"Failed to remove close button.", LOGTYPE_ERROR, true);
				return false;
			}
		}

	}

	//Logger::Log(_T("Window is Initialized.", LOGTYPE_INFO, false);
	
	// No screw ups? Good, that means the initialization was successful.
	return true;
 }







bool Window::Update(Context& context)
{

	//Small note, the brackets { & } don't necessarily need to be apart of the code for this, the compiler will automatically seperate them up if necessary.
	//Borders such as those are usually required if you want to parse out your code.
	if(context.pWnd != this) 
		context.pWnd = this;

	return true;

	}
bool Window::ShutDown()
{
	if (m_bFullscreen)
	{
		ChangeDisplaySettings(NULL, 0);
		ShowCursor(true);
	}

	//Are we able to release the DC?

	//Set the DC to null.
	if (m_hDC && !ReleaseDC(m_hWindow, m_hDC))
	{
		//Logger::Log(_T("Release DC failed.");
		m_hDC = NULL;
		return false;
	}

	if (m_hWindow && !DestroyWindow(m_hWindow))
	{
		//Logger::Log(_T("Destroy Window command failed.");
		m_hWindow = NULL;
		return false;
	}

	if (!UnregisterClass(m_Title.c_str(),m_Inst))
	{
		//Logger::Log(_T("Could Not unregister the class.");
		m_Inst = NULL;
		return false;
	}

	return true;
 }