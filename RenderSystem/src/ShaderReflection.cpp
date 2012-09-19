#include "ShaderReflecton.h"
using namespace sturm;

ShaderReflection::ShaderReflection() {}
ShaderReflection::~ShaderReflection() {}

void ShaderReflection::Reflect(ID3D10Blob* shader) {
	ID3D11ShaderReflection* reflector = 0;
	D3D11_SIGNATURE_PARAMETER_DESC input, output;
	D3D11_SHADER_INPUT_BIND_DESC resource; //Bind point is the register location


	D3DReflect(shader->GetBufferPointer(), shader->GetBufferSize(), 
		IID_ID3D11ShaderReflection, (void**)&reflector);

	reflector->GetDesc(&shaderDesc);

	inputParams.paramCount = shaderDesc.InputParameters;
	inputParams.params = new D3D11_SIGNATURE_PARAMETER_DESC[inputParams.paramCount];
	for(u32 i = 0; i < shaderDesc.InputParameters; ++i) {
		reflector->GetInputParameterDesc(i, &input);
		inputParams.params[i] = input;
	}

	outputParams.paramCount = shaderDesc.OutputParameters;
	outputParams.params = new D3D11_SIGNATURE_PARAMETER_DESC[outputParams.paramCount];
	for(u32 i = 0; i < shaderDesc.OutputParameters; ++i) {
		reflector->GetOutputParameterDesc(i, &output);
		outputParams.params[i] = output;
	}

	for(u32 i = 0; i < shaderDesc.BoundResources; ++i) {
		reflector->GetResourceBindingDesc(i, &resource);
		
		if(resource.Type == D3D_SIT_CBUFFER) {
			ProcessCbuffer(reflector->GetConstantBufferByName(resource.Name));
		}
		else if(resource.Type == D3D_SIT_SAMPLER) {

		}
		else if(resource.Type == D3D_SIT_TEXTURE) {
			
		}
		else {}
	}
}


void ShaderReflection::ProcessCbuffer(ID3D11ShaderReflectionConstantBuffer* cb) {
	D3D11_SHADER_VARIABLE_DESC svd;
	D3D11_SHADER_TYPE_DESC std;
	ID3D11ShaderReflectionVariable* var;
	ID3D11ShaderReflectionType* type;
	VarType vt;
	Variable v;
	ConstantBuffer buffer;

	cb->GetDesc(&buffer.desc);
	
	for(u32 j = 0; j < buffer.desc.Variables; ++j) {
		vt = Unknown;
		var = cb->GetVariableByIndex(j);
		type = var->GetType();
		var->GetDesc(&svd);
		type->GetDesc(&std);

		switch(std.Class) {
		case D3D_SVC_MATRIX_COLUMNS:
			{
				if(std.Rows == 4 && std.Columns == 4)		{ vt = Matrix4x4; }
				else if(std.Rows == 3 && std.Columns == 3)	{ vt = Matrix3x3; }
				break;
			}
		case D3D_SVC_VECTOR:
			{
				if(std.Columns == 4)		{ vt = Vector4; }
				else if(std.Columns == 3)	{ vt = Vector3; }
				else if(std.Columns == 2)	{ vt = Vector2; }
				break;
			}
		case D3D_SVC_SCALAR:
			{
				if(std.Type == D3D_SVT_FLOAT)		{	vt = Float;	}
				else if(std.Type == D3D_SVT_INT)	{	vt = Integer;	}
				break;
			}
		default:
			{
				break;
			}
		}
		v.startOffset	= svd.StartOffset;
		v.elements		= std.Elements;
		v.name			= svd.Name;
		v.type			= vt;
		buffer.vars.push_back(v);
	}
	cbuffers.push_back(buffer);
}

DXGI_FORMAT ShaderReflection::GetDXGIFormat(D3D11_SIGNATURE_PARAMETER_DESC pd) {
	BYTE mask = pd.Mask;
	int varCount = 0;
	while(mask)
	{
		if(mask & 0x01) varCount++;
		mask = mask >> 1;
	}

	if(pd.ComponentType == D3D_REGISTER_COMPONENT_FLOAT32)
	{
		if(varCount == 4) return DXGI_FORMAT_R32G32B32A32_FLOAT;
		else if(varCount == 3) return DXGI_FORMAT_R32G32B32_FLOAT;
		else if(varCount == 2) return DXGI_FORMAT_R32G32_FLOAT;
		else if(varCount == 1) return DXGI_FORMAT_R32_FLOAT;	
	}
	else if(pd.ComponentType == D3D_REGISTER_COMPONENT_SINT32)
	{
		if(varCount == 4) return DXGI_FORMAT_R32G32B32A32_SINT;
		else if(varCount == 3) return DXGI_FORMAT_R32G32B32_SINT;
		else if(varCount == 2) return DXGI_FORMAT_R32G32_SINT;
		else if(varCount == 1) return DXGI_FORMAT_R32_SINT;
	}
	else if(pd.ComponentType == D3D_REGISTER_COMPONENT_UINT32)
	{
		if(varCount == 4) return DXGI_FORMAT_R32G32B32A32_UINT;
		else if(varCount == 3) return DXGI_FORMAT_R32G32B32_UINT;
		else if(varCount == 2) return DXGI_FORMAT_R32G32_UINT;
		else if(varCount == 1) return DXGI_FORMAT_R32_UINT;
	}	
	else if(pd.ComponentType == D3D_REGISTER_COMPONENT_UNKNOWN)
	{}
	else
	{}

	return DXGI_FORMAT_UNKNOWN;
}