#ifndef _pixelshader_h_
#define _pixelshader_h_

#include "D3D11Util.h"
#include "Util.h"
#include <D3DX11async.h>
#include <string>

namespace sturm {

	class PixelShader {
	public:
		PixelShader(ID3D11Device* device);
		~PixelShader();

		void Compile(std::wstring fpath);
	private:
		void Error(ID3D10Blob* msg);
	private:
		ID3D11Device* _device;
		ID3D11PixelShader* _shader;
	};

} //namespace

#endif