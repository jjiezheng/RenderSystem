#include "Window.h"

/** 
	Process messages for the Window
**/
LRESULT Window::MessageHandler(UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch(msg)
	{
	case WM_MOUSEMOVE:
		break;
	case WM_LBUTTONDOWN:
		break;
	case WM_RBUTTONDOWN:
		break;
	case WM_LBUTTONUP:
		break;
	case WM_RBUTTONUP:
		break;
	case WM_KEYDOWN:
		if(wParam == VK_ESCAPE) PostQuitMessage(0);
		break;
	case WM_KEYUP:
		break;
	case WM_SIZE: //User resizes window
		_clientWidth = LOWORD(lParam);
		_clientHeight = HIWORD(lParam);
		switch(wParam)
		{
		case SIZE_MINIMIZED:
			_minimized = true;
			_maximized = false;
			break;
		case SIZE_MAXIMIZED:
			_minimized = false;
			_maximized = true;
			break;
		case SIZE_RESTORED:
			if(_minimized) { //check previous state
				_minimized = false;
			}	
			else if(_maximized) {
				_maximized = false;
			}
			else if(_resizing) { /*do nothing while user is still resizing*/ }
			else {}
			break;
		}
		return 0;
	case WM_ENTERSIZEMOVE: //Users grabs resize bars
		_resizing = true;
		return 0;
	case WM_EXITSIZEMOVE: //User releases resize bars
		_resizing = false;
		OnResize();
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	case WM_GETMINMAXINFO: //Prevent window from becoming too small
		((MINMAXINFO*)lParam)->ptMinTrackSize.x = 200;
		((MINMAXINFO*)lParam)->ptMinTrackSize.y = 200;
		return 0;
	case WM_SYSCOMMAND:
		switch(wParam)
		{
		case SC_CLOSE:  //Application being closed
			break;
		case SC_SCREENSAVE: //ScreenSaver
			break;
		case SC_MONITORPOWER: //Power saving mode
			break;
		}
		break;
	}

	return DefWindowProc(_hWnd, msg, wParam, lParam);
}


/**
	Once a WM_CREATE command is received, reroute messages to the 
	created window.
**/
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	static Window* appWindow = 0;

	switch(msg)
	{
	case WM_CREATE:
		CREATESTRUCT* cs = (CREATESTRUCT*)lParam;
		appWindow = (Window*)cs->lpCreateParams;
		return 0;
	}

	if(appWindow)
		return appWindow->MessageHandler(msg, wParam, lParam);
	else 
		return DefWindowProc(hWnd, msg, wParam, lParam);
}

/**
	Initialize Window's private member variables
**/
Window::Window(int width, int height, wstring windowTitle)
	: _clientWidth(width), _clientHeight(height), _hInstance(0), _hWnd(0),
	_maximized(false), _minimized(false), _resizing(false), _windowTitle(windowTitle)
{
	InitializeWindow();
}

Window::~Window()
{}

int Window::GetWidth() { return _clientWidth; }
int Window::GetHeight() { return _clientHeight; }
HWND Window::GetHandle() { return _hWnd; }

/**
	Create a Win32 window
**/
void Window::InitializeWindow()
{
	WNDCLASSEX wcex;

	_hInstance = GetModuleHandle(NULL);

	wcex.cbSize			= sizeof(WNDCLASSEX);
	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= _hInstance;
	wcex.hIcon			= LoadIcon(NULL, IDI_APPLICATION);
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= 0;
	wcex.lpszClassName	= _windowTitle.c_str();
	wcex.hIconSm		= 0;

	if(!RegisterClassEx(&wcex))
	{
		ERROR_MB(L"Failed to Register WndClass");
		PostQuitMessage(0);
	}

	UINT styleBorderless = WS_EX_TOPMOST | WS_POPUP;
	UINT styleNormal = WS_OVERLAPPEDWINDOW;

	RECT R = {0, 0, _clientWidth, _clientHeight};
	AdjustWindowRect(&R, WS_OVERLAPPEDWINDOW, false);
	_hWnd = CreateWindow(_windowTitle.c_str(), _windowTitle.c_str(), 
			 styleNormal, CW_USEDEFAULT, CW_USEDEFAULT, _clientWidth, _clientHeight, 
			 0, 0, _hInstance, this);
	if(!_hWnd)
	{
		ERROR_MB(L"Create Window Failed");
		PostQuitMessage(0);
	}

	ShowWindow(_hWnd, SW_SHOW);
	SetForegroundWindow(_hWnd);
	SetFocus(_hWnd);
	UpdateWindow(_hWnd);
	_maximized = true;
	
}

void Window::SetWindowCaption(const std::wstring caption)
{
	SetWindowText(_hWnd, _windowTitle.append(L": ").append(caption).c_str());
}


void Window::OnResize() {

}