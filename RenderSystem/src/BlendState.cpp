#include "BlendState.h"
using namespace sturm;

BlendState::BlendState() {

	AlphaToCoverageEnable					= false;
	IndependentBlendEnable					= false;
	RenderTarget[0].BlendEnable				= false;
	RenderTarget[0].SrcBlend				= D3D11_BLEND_ONE;
	RenderTarget[0].DestBlend				= D3D11_BLEND_ZERO;
	RenderTarget[0].BlendOp					= D3D11_BLEND_OP_ADD;
	RenderTarget[0].SrcBlendAlpha			= D3D11_BLEND_ONE;
	RenderTarget[0].DestBlendAlpha			= D3D11_BLEND_ZERO;
	RenderTarget[0].BlendOpAlpha			= D3D11_BLEND_OP_ADD;
	RenderTarget[0].RenderTargetWriteMask	= D3D11_COLOR_WRITE_ENABLE_ALL;
}

BlendState::~BlendState() {

}

bool BlendState::operator==(D3D11_BLEND_DESC bd) {
	return !memcmp(this, &bd, sizeof(D3D11_BLEND_DESC));
}
bool BlendState::operator==(BlendState& bs) {
	return !memcmp(this, &bs, sizeof(D3D11_BLEND_DESC));
}
