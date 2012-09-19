#ifndef _window_h_
#define _window_h_

#include <windows.h>
#include <string>
using namespace std;

#define ERROR_MB(x) MessageBox(NULL, x, L"ERROR", MB_OK | MB_ICONEXCLAMATION);

class Window
{
public:
	Window(int width, int height, wstring title);
	~Window();

	int GetWidth();
	int GetHeight();
	HWND GetHandle();

	LRESULT MessageHandler(UINT msg, WPARAM wParam, LPARAM lParam);
	void SetWindowCaption(const std::wstring caption);
private:
	void InitializeWindow();
	void OnResize();

private:
	HINSTANCE	_hInstance;
	HWND		_hWnd;
	wstring		_windowTitle;

	bool _minimized;
	bool _maximized;
	bool _resizing;

	int _clientWidth;
	int _clientHeight;

};

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

#endif
