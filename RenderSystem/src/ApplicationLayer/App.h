#ifndef _app_h_
#define _app_h_

#include "window.h"
#include "timer.h"
#include "../RenderSystem.h"

using namespace std;

class App
{
public:
	~App();
	void RunApp();
private:
	void InitApp();
	void Update();
	void Frame();
	void Run();	
private:
	Window* _window;
	Timer* _timer;
	

	sturm::RenderSystem* _renderSystem;

};

#endif