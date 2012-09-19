#include "IndexBuffer.h"
using namespace sturm;

IndexBuffer::IndexBuffer() {
	BindFlags			= D3D11_BIND_INDEX_BUFFER;
	ByteWidth			= 0;
	CPUAccessFlags		= 0;
	MiscFlags			= 0;
	StructureByteStride = 0;
	Usage				= D3D11_USAGE_DEFAULT;
	pSysMem				= 0;
	SysMemPitch			= 0;
	SysMemSlicePitch	= 0;
}

void IndexBuffer::AttachData(const void* data, int _indexCount, int byteWidth) {
	pSysMem = data;
	_indexCount = _indexCount;
	ByteWidth = byteWidth * _indexCount;
}

void IndexBuffer::SetUsage(D3D11_USAGE usage) {
	if(usage == D3D11_USAGE_DYNAMIC) {
		CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		Usage = usage;
	}
	else {
		Usage = usage;
	}
}