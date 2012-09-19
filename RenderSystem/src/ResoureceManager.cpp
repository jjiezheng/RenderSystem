#include "ResourceManager.h"
using namespace sturm;
using namespace std;

int ResourceManager::_handleID = 0;

ResourceManager::ResourceManager(ID3D11Device* device)
	: _device(device) {

}

ResourceManager::~ResourceManager() {
	ReleaseCOM(_device);
	//clear states
}

int ResourceManager::AddBlendState(BlendState bs) {
	//check if we already have the blendstate
	D3D11_BLEND_DESC bd;
	map<int, ID3D11BlendState*>::iterator it = _blendStates.begin();
	for(;it != _blendStates.end(); ++it) {
		it->second->GetDesc(&bd);
		if(bs == bd) {
			return it->first;
		}
	}
	//create new blendstate
	ID3D11BlendState* blendState;
	_device->CreateBlendState(&bs, &blendState);
	_blendStates[++_handleID] = blendState;
	return _handleID;
}

int ResourceManager::AddRasterState(RasterState rs) {
	D3D11_RASTERIZER_DESC rd;
	map<int, ID3D11RasterizerState*>::iterator it = _rasterStates.begin();
	for(;it != _rasterStates.end(); ++it) {
		it->second->GetDesc(&rd);
		if(rs == rd) {
			return it->first;
		}
	}
	//create new rasterstate
	ID3D11RasterizerState* rasterState;
	_device->CreateRasterizerState(&rd, &rasterState);
	_rasterStates[++_handleID] = rasterState;
	return _handleID;
}

int ResourceManager::AddDepthStencilState(DepthStencilState dss) {
	D3D11_DEPTH_STENCIL_DESC dsd;
	map<int, ID3D11DepthStencilState*>::iterator it = _depthstencilStates.begin();
	for(;it != _depthstencilStates.end(); ++it) {
		it->second->GetDesc(&dsd);
		if(dss == dsd) {
			return it->first;
		}
	}
	//create new depthstencil state
	ID3D11DepthStencilState* depthStencilState;
	_device->CreateDepthStencilState(&dsd, &depthStencilState);
	_depthstencilStates[++_handleID] = depthStencilState;
	return _handleID;
}

int ResourceManager::AddVertexBuffer(VertexBuffer vb) {
	D3D11_BUFFER_DESC bd;
	map<int, ID3D11Buffer*>::iterator it = _vbs.begin();
	for(;it != _vbs.end(); ++it) {
		it->second->GetDesc(&bd);
		
		//if(vb == bd) {
		//	return it->first;
		//}
	}
	//create new depthstencil state
	ID3D11Buffer* buffer;
	_device->CreateBuffer(&vb, (D3D11_SUBRESOURCE_DATA*)&vb, &buffer);
	_vbs[++_handleID] = buffer;

	return _handleID;
}

int ResourceManager::AddIndexBuffer(IndexBuffer ib) {

	return -1;
}