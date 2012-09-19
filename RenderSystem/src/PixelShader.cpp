#include "PixelShader.h"
using namespace sturm;

PixelShader::PixelShader(ID3D11Device* device)
	: _device(device)
{

}

PixelShader::~PixelShader() {
	ReleaseCOM(_device);
}

void PixelShader::Compile(std::wstring fpath) {
	HRESULT hret;
	ID3D10Blob* buffer, *msg;


	u32 flags1 = 0; u32 flags2 = 0;
	flags1 |= D3D10_SHADER_ENABLE_STRICTNESS;

	hret = D3DX11CompileFromFile(fpath.c_str(), 0, 0, "main", "ps_5_0", flags1, flags2, 0, &buffer, &msg, 0);
	if(FAILED(hret)) {
		if(msg) { Error(msg); }
		else {
			float f = 5;
		}
	}

	hret = _device->CreatePixelShader(buffer->GetBufferPointer(), buffer->GetBufferSize(), 0, &_shader);
	if(FAILED(hret)) {

	}

	ReleaseCOM(buffer);
}

void PixelShader::Error(ID3D10Blob* msg) {
	std::string m((char*)msg->GetBufferPointer());
	OutputDebugStringA("\n");
	OutputDebugStringA(m.c_str());
	OutputDebugStringA("\n");
	exit(0);
}