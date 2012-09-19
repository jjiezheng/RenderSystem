#include "app.h"
#include "../RenderState.h"
#include "../RenderInstance.h"
using namespace std;

App::~App()
{
}
void App::RunApp() {
	InitApp();
	Run();
}

void App::InitApp()
{
	_timer = new Timer();
	_window = new Window(800, 600, L"Direct3D");

	_renderSystem = new sturm::RenderSystem(_window);
	sturm::RenderState rs;
	rs.rasterState.CullMode = D3D11_CULL_NONE;
	rs.topology = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
	sturm::RenderInstance* ri = _renderSystem->ValidateInstance(rs);
}

void App::Update() {
	_renderSystem->Update();
}

void App::Frame() {
	_renderSystem->Frame();
}

void App::Run()
{
	bool done = false;
	MSG msg;

	while(!done)
	{
		if(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if(msg.message == WM_QUIT) { done = true; }
			else
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
		{
			_timer->Frame();
			Update();
			Frame();
		}
	}
}