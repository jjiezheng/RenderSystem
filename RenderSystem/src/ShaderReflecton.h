#ifndef _shaderreflection_h_
#define _shaderreflection_h_

#include "D3D11Util.h"
#include <D3DX11async.h>
#include <D3Dcompiler.h>
#include <string>
#include "Util.h"
#include <vector>

#pragma comment(lib, "d3dcompiler.lib")
#pragma comment(lib, "dxguid.lib")

namespace sturm {

	enum VarType {
		Matrix4x4,
		Matrix3x3,
		Vector4,
		Vector3,
		Vector2,
		Float,
		Integer,
		Unknown
	};

	struct SignatureParams {
		int paramCount;
		D3D11_SIGNATURE_PARAMETER_DESC* params;
	};

	struct Variable {
		std::string name;
		VarType type;
		int startOffset;
		int elements;
	};
	struct ConstantBuffer {
		D3D11_SHADER_BUFFER_DESC desc;
		std::vector<Variable> vars;
	};


	class ShaderReflection {
	public:
		ShaderReflection();
		~ShaderReflection();

		void Reflect(ID3D10Blob* shader);
		DXGI_FORMAT GetDXGIFormat(D3D11_SIGNATURE_PARAMETER_DESC pd);
	private:
		void ProcessCbuffer(ID3D11ShaderReflectionConstantBuffer* cb);
	public:
		SignatureParams inputParams;
		SignatureParams outputParams;
		std::vector<ConstantBuffer> cbuffers;
		D3D11_SHADER_DESC shaderDesc;
	};

} //namespace

#endif