#include "RasterState.h"
using namespace sturm;

RasterState::RasterState() {
	AntialiasedLineEnable	= false;
	CullMode				= D3D11_CULL_BACK;
	DepthBias				= 0;
	DepthBiasClamp			= 0.0f;
	FillMode				= D3D11_FILL_SOLID;
	FrontCounterClockwise	= false;
	MultisampleEnable		= false;
	ScissorEnable			= false;
	SlopeScaledDepthBias	= 0.0f;
}

RasterState::~RasterState() {}