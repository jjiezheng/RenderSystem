#ifndef _inputlayout_h_
#define _inputlayout_h_

#include "D3D11Util.h"

namespace sturm {

	struct InputLayout {
		InputLayout() : layout(0), elementCount(0), layoutDesc(0) {};
		int elementCount;
		D3D11_INPUT_ELEMENT_DESC* layoutDesc;
		ID3D11InputLayout* layout;
	};
} //namespace

#endif