#ifndef _renderstate_h_
#define _renderstate_h_

#include "RasterState.h"
#include "BlendState.h"
#include "DepthStencilState.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include <string>

namespace sturm {

	class RenderState {
	public:
		RenderState();
		~RenderState();
		bool isValidated();
	private:
		bool _validated;
	public:
		RasterState rasterState;
		BlendState blendState;
		DepthStencilState depthStencilState;
		D3D11_PRIMITIVE_TOPOLOGY topology;
		VertexBuffer vertexBuffer;
		IndexBuffer indexBuffer;
		/* 
		Shader
		ShaderParams
		RenderTarget
		*/
	};


} //namespace

#endif