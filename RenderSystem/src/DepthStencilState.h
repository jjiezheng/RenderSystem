#ifndef _depthstencilstate_h_
#define _depthstencilstate_h_

#include "D3D11Util.h"

namespace sturm {

	class DepthStencilState : public D3D11_DEPTH_STENCIL_DESC {
	public:
		DepthStencilState();
		~DepthStencilState();
		bool operator==(D3D11_DEPTH_STENCIL_DESC dsd)	{ return !memcmp(this, &dsd, sizeof(D3D11_DEPTH_STENCIL_DESC)); };
		bool operator==(DepthStencilState& dss)			{ return !memcmp(this, &dss, sizeof(D3D11_DEPTH_STENCIL_DESC)); };
	private:
	};

} //namespace

#endif