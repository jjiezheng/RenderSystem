#ifndef _renderparameters_h_
#define _renderparameters_h_

#include "D3D11Util.h"

namespace sturm {

	class RenderParameters {
	public:
		D3D11_PRIMITIVE_TOPOLOGY topology;
		int rsHandle;
		int bsHandle;
		int dssHandle;
	};

} //namespace

#endif