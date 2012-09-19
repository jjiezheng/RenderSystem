#ifndef _rasterstate_h_
#define _rasterstate_h_

#include "D3D11Util.h"

namespace sturm {

	class RasterState : public D3D11_RASTERIZER_DESC {
	public:
		RasterState();
		~RasterState();
		bool operator==(D3D11_RASTERIZER_DESC rd)	{ return !memcmp(this, &rd, sizeof(D3D11_RASTERIZER_DESC)); };
		bool operator==(RasterState& rs)			{ return !memcmp(this, &rs, sizeof(D3D11_RASTERIZER_DESC)); };
	private:
	public:
	};

} //namespace

#endif