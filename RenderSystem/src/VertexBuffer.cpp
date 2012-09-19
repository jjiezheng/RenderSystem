#include "VertexBuffer.h"
using namespace sturm;

VertexBuffer::VertexBuffer() {
	BindFlags			= D3D11_BIND_VERTEX_BUFFER;
	ByteWidth			= 0;
	CPUAccessFlags		= 0;
	MiscFlags			= 0;
	StructureByteStride = 0;
	Usage				= D3D11_USAGE_DEFAULT;
	pSysMem				= 0;
	SysMemPitch			= 0;
	SysMemSlicePitch	= 0;
}

void VertexBuffer::AttachData(const void* data, int vertexCount, int byteWidth) {
	pSysMem = data;
	_vertexCount = vertexCount;
	ByteWidth = byteWidth * _vertexCount;
}

void VertexBuffer::SetUsage(D3D11_USAGE usage) {
	if(usage == D3D11_USAGE_DYNAMIC) {
		CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		Usage = usage;
	}
	else {
		Usage = usage;
	}
}