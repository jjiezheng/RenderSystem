#ifndef _blendstate_h_
#define _blendstate_h_

#include "D3D11Util.h"

namespace sturm {

	class BlendState : public D3D11_BLEND_DESC {
	public:
		BlendState();
		~BlendState();
		bool operator==(D3D11_BLEND_DESC bd);
		bool operator==(BlendState& bd);
	private:
	};

} //namespace

#endif