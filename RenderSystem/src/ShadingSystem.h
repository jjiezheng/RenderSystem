#ifndef _shadingsystem_h_
#define _shadingsystem_h_

#include "D3D11Util.h"
#include "PixelShader.h"
#include "VertexShader.h"
#include "InputLayout.h"
#include <string>
#include <map>
#include <vector>

namespace sturm {

	class ShadingSystem {
	public:
		ShadingSystem(ID3D11Device* device, ID3D11DeviceContext* context);
		~ShadingSystem();
		void FindShaders();
	private:
		void CreateInputLayouts();
		bool CompareLayouts(InputLayout* layout1, InputLayout* layout2);
	private:
		std::wstring			_shadersPath;
		ID3D11Device*			_device;
		ID3D11DeviceContext*	_context;

		std::map<std::wstring, PixelShader*>	_ps;
		std::map<std::wstring, VertexShader*>	_vs;
		std::vector<InputLayout*>				_inputLayouts;
	};

} //namespace
#endif