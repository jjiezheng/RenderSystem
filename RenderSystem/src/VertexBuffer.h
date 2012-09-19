#ifndef _vertexbuffer_h_
#define _vertexbuffer_h_

#include "D3D11Util.h"

namespace sturm {
 
	class VertexBuffer : public D3D11_BUFFER_DESC, D3D11_SUBRESOURCE_DATA {
	public:
		VertexBuffer();
		void AttachData(const void* data, int vertexCount, int byteWidth);
		void SetUsage(D3D11_USAGE usage);
	private:
		int _vertexCount;
	};

} //namespace
#endif