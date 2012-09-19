#include "RenderSystem.h"
using namespace sturm;

RenderSystem::RenderSystem(Window* window)
: _renderWindow(window) {

	_renderModule		= new RendererD3D11(_renderWindow->GetWidth(), 
		_renderWindow->GetHeight(), _renderWindow->GetHandle());

	_shadingSystem		= new ShadingSystem(_renderModule->GetDevice(), 
		_renderModule->GetContext());

	_resourceManager	= new ResourceManager(_renderModule->GetDevice());
	
}

RenderSystem::~RenderSystem() {

}

RenderInstance* RenderSystem::ValidateInstance(RenderState rs) {
	RenderInstance* ri = new RenderInstance();
	ri->state = &rs;
	ri->blendStateHandle		= _resourceManager->AddBlendState(rs.blendState);
	ri->rasterStateHandle		= _resourceManager->AddRasterState(rs.rasterState);
	ri->depthStencilStateHandle = _resourceManager->AddDepthStencilState(rs.depthStencilState);
	ri->vbHandle				= _resourceManager->AddVertexBuffer(rs.vertexBuffer);
	ri->ibHandle				= _resourceManager->AddIndexBuffer(rs.indexBuffer);

	return ri;
}

RenderGroup* RenderSystem::ValidateGroup(std::vector<RenderState> rsGroup) {
	return NULL;
}

void RenderSystem::Update() {
	
}

void RenderSystem::Frame() {
	_renderModule->Clear(0.5f);
	_renderModule->Present();
}