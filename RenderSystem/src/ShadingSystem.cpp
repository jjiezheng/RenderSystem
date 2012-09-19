#include "ShadingSystem.h"
using namespace sturm;
using namespace std;

ShadingSystem::ShadingSystem(ID3D11Device* device, ID3D11DeviceContext* context) 
: _device(device), _context(context) {
	
	TCHAR buff[MAX_PATH];
	GetCurrentDirectory(MAX_PATH, buff);
	_shadersPath = buff;
	_shadersPath.append(L"\\hlsl\\");

	FindShaders();
}

ShadingSystem::~ShadingSystem() {

}

void ShadingSystem::FindShaders() {
	wstring search = _shadersPath;
	search.append(L"*");

	HANDLE hFind = INVALID_HANDLE_VALUE;
	WIN32_FIND_DATA ffd;
	hFind = FindFirstFile(search.c_str(), &ffd);

	while(FindNextFile(hFind, &ffd) != 0) {
		if(ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) //directory, dont care
		{}
		else { //file, check if a shader
			std::wstring fname = ffd.cFileName;
			if(fname.find(L".psh") != std::string::npos) {
				_ps[fname] = new PixelShader(_device);
				_ps[fname]->Compile(_shadersPath.append(fname));
			} else if(fname.find(L".vsh") != std::string::npos) {
				_vs[fname] = new VertexShader(_device);
				_vs[fname]->Compile(_shadersPath.append(fname));
			} else if(fname.find(L".csh") != std::string::npos) {

			} else if(fname.find(L".gsh") != std::string::npos) {

			} else if(fname.find(L".hsh") != std::string::npos) {

			} else if(fname.find(L".dsh") != std::string::npos) {

			}
		}
	}
	CreateInputLayouts();
}

void ShadingSystem::CreateInputLayouts() {
	D3D11_INPUT_ELEMENT_DESC* layoutDesc;
	InputLayout layout;
	ShaderReflection* sr;
	D3D11_SIGNATURE_PARAMETER_DESC param;
	bool createLayout;
	int elementCount = 0;


	std::map<std::wstring, VertexShader*>::iterator it = _vs.begin();
	for(; it != _vs.end(); ++it) {
		//create layout description
		sr = &(it->second->params);
		elementCount = sr->inputParams.paramCount;
		layoutDesc = new D3D11_INPUT_ELEMENT_DESC[elementCount];
		for(u32 i = 0; i < elementCount; ++i) {
			param = sr->inputParams.params[i];
			layoutDesc[i].SemanticName			= param.SemanticName;
			layoutDesc[i].SemanticIndex			= param.SemanticIndex;
			layoutDesc[i].Format				= sr->GetDXGIFormat(param);
			layoutDesc[i].InputSlot				= 0;
			layoutDesc[i].InstanceDataStepRate	= 0;
			layoutDesc[i].InputSlotClass	= D3D11_INPUT_PER_VERTEX_DATA;
			if(i == 0)
				layoutDesc[i].AlignedByteOffset = 0;
			else
				layoutDesc[i].AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
		}

		layout.elementCount = elementCount;
		layout.layoutDesc   = layoutDesc;

		//check if a layout already exists
		createLayout = true;
		std::vector<InputLayout*>::iterator iter;
		iter = _inputLayouts.begin();
		for(; iter != _inputLayouts.end(); ++iter) {
			if(CompareLayouts(&layout, *iter)) { createLayout = false; }	
		}

		//create if layout doesnt exist
		if(createLayout) {
			(*it).second->CreateInputLayout(layout.layoutDesc, layout.elementCount, layout.layout);
			_inputLayouts.push_back(new InputLayout(layout));
		}
	}
}

bool ShadingSystem::CompareLayouts(InputLayout* layout1, InputLayout* layout2) {
	if(layout1->elementCount != layout2->elementCount) return false;
	D3D11_INPUT_ELEMENT_DESC param1, param2;
	for(u32 i = 0; i < layout1->elementCount; ++i) {
		param1 = layout1->layoutDesc[i];
		param2 = layout2->layoutDesc[i];

		//name doesnt need to match
		if(param1.SemanticIndex != param2.SemanticIndex)				return false;
		if(param1.Format != param2.Format)								return false;
		if(param1.InputSlot != param2.InputSlot)						return false;
		if(param1.InstanceDataStepRate != param2.InstanceDataStepRate)	return false;
		if(param1.InputSlotClass != param2.InputSlotClass)				return false;
	}
	return true;
}