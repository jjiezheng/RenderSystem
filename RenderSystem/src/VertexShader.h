#ifndef _vertexshader_h_
#define _vertexshader_h_

#include "D3D11Util.h"
#include "Util.h"
#include <D3DX11async.h>
#include <string>
#include "ShaderReflecton.h"

namespace sturm {

	class VertexShader {
	public:
		VertexShader(ID3D11Device* device);
		~VertexShader();

		void Compile(std::wstring fpath);
		void CreateInputLayout(D3D11_INPUT_ELEMENT_DESC* layout, int elementCount, ID3D11InputLayout* inputLayout);
	private:
		void Error(ID3D10Blob* msg);
	private:
		ID3D11Device*		_device;
		ID3D11VertexShader* _shader;
		ID3D10Blob*			_blob;
	public:
		ShaderReflection params;
	};

} //namespace

#endif