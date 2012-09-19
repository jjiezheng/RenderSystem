#ifndef _rendersystem_h_
#define _rendersystem_h_

#include "RendererD3D11.h"
#include "ResourceManager.h"
#include "RenderState.h"
#include "ShadingSystem.h"
#include "ApplicationLayer\Window.h"
#include "RenderInstance.h"
#include "RenderGroup.h"
#include <vector>

namespace sturm {
	
	class RenderSystem {
	public:
		RenderSystem(Window* window); 
		~RenderSystem();

		RenderInstance* ValidateInstance(RenderState rs);
		RenderGroup*    ValidateGroup(std::vector<RenderState> rsGroup);

		void Update();
		void Frame();
		
	private:
		Window*				_renderWindow;
		RendererD3D11*		_renderModule;
		ResourceManager*	_resourceManager;
		ShadingSystem*		_shadingSystem;



	};
} //namespace

#endif