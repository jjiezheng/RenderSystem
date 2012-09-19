#ifndef _resourcemanager_h_
#define _resourcemanager_h_

#include "D3D11Util.h"
#include "RenderState.h"
#include <map>



namespace sturm {

	//Manages buffers states and textures 

	class ResourceManager {
	public:
		ResourceManager(ID3D11Device* device);
		~ResourceManager();
		
		int AddBlendState(BlendState bs);
		int AddRasterState(RasterState rs);
		int AddDepthStencilState(DepthStencilState dss);
		int AddVertexBuffer(VertexBuffer vb);
		int AddIndexBuffer(IndexBuffer ib);
	private:
		static int _handleID;
		ID3D11Device* _device;
		std::map<int, ID3D11BlendState*>			_blendStates;
		std::map<int, ID3D11RasterizerState*>		_rasterStates;
		std::map<int, ID3D11DepthStencilState*>		_depthstencilStates;
		std::map<int, ID3D11Buffer*>				_vbs;
		std::map<int, ID3D11Buffer*>				_ibs;
	};

} //namespace

#endif