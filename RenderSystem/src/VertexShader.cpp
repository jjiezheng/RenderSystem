#include "VertexShader.h"
using namespace sturm;

VertexShader::VertexShader(ID3D11Device* device)
	: _device(device)
{

}

VertexShader::~VertexShader() {
	ReleaseCOM(_device);
	ReleaseCOM(_blob);
}

void VertexShader::Compile(std::wstring fpath) {
	HRESULT hret;
	ID3D10Blob *msg;

	
	u32 flags1 = 0; u32 flags2 = 0;
	flags1 |= D3D10_SHADER_ENABLE_STRICTNESS;

	hret = D3DX11CompileFromFile(fpath.c_str(), 0, 0, "main", "vs_5_0", flags1, flags2, 0, &_blob, &msg, 0);
	if(FAILED(hret)) {
		if(msg) { Error(msg); }
		else {
			float f = 5;
		}
	}
	params.Reflect(_blob);

	hret = _device->CreateVertexShader(_blob->GetBufferPointer(), _blob->GetBufferSize(), 0, &_shader);
	if(FAILED(hret)) {

	}
	
}

void VertexShader::Error(ID3D10Blob* msg) {
	std::string m((char*)msg->GetBufferPointer());
	OutputDebugStringA("\n");
	OutputDebugStringA(m.c_str());
	OutputDebugStringA("\n");
	exit(0);
}

void VertexShader::CreateInputLayout(D3D11_INPUT_ELEMENT_DESC* layout, int elementCount, ID3D11InputLayout* inputLayout) {
	HRESULT hret; 
	hret = _device->CreateInputLayout(layout, elementCount, _blob->GetBufferPointer(), _blob->GetBufferSize(), &inputLayout);
	if(FAILED(hret))
	{}
}