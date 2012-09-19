#include "DepthStencilState.h"
using namespace sturm;

DepthStencilState::DepthStencilState() {
	DepthEnable						= true;
	DepthWriteMask					= D3D11_DEPTH_WRITE_MASK_ALL;
	DepthFunc						= D3D11_COMPARISON_LESS;
	StencilEnable					= true;
	StencilReadMask					= 0xFF;
	StencilWriteMask				= 0xFF;
	FrontFace.StencilFailOp			= D3D11_STENCIL_OP_KEEP;
	FrontFace.StencilDepthFailOp	= D3D11_STENCIL_OP_INCR;
	FrontFace.StencilPassOp			= D3D11_STENCIL_OP_KEEP;
	FrontFace.StencilFunc			= D3D11_COMPARISON_ALWAYS;
	BackFace.StencilFailOp			= D3D11_STENCIL_OP_KEEP;
	BackFace.StencilDepthFailOp		= D3D11_STENCIL_OP_DECR;
	BackFace.StencilPassOp			= D3D11_STENCIL_OP_KEEP;
	BackFace.StencilFunc			= D3D11_COMPARISON_ALWAYS;
}

DepthStencilState::~DepthStencilState() {

}