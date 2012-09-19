#ifndef _renderinstance_h_
#define _renderinstance_h_

#include "RenderState.h"

namespace sturm {

	class RenderInstance {
	public:
		//sort key for render order
		RenderState* state;
		int blendStateHandle;
		int rasterStateHandle;
		int depthStencilStateHandle;
		int vbHandle;
		int ibHandle;

	};


} //namespace

#endif