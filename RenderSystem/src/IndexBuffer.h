#ifndef _indexbuffer_h_
#define _indexbuffer_h_

#include "D3D11Util.h"

namespace sturm {

	class IndexBuffer : public D3D11_BUFFER_DESC, D3D11_SUBRESOURCE_DATA {
	public:
		IndexBuffer();
		void AttachData(const void* data, int indexCount, int byteWidth);
		void SetUsage(D3D11_USAGE usage);
	private:
		int _indexCount;
	};

} //namespace
#endif