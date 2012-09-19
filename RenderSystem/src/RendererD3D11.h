#ifndef _rendererD3D11_h_
#define _rendererD3D11_h_

#include "D3D11Util.h"
#include "EnumerateAdapters.h"

namespace sturm {
	class RendererD3D11 {
	public:
		RendererD3D11(int width, int height, HWND hWnd, 
			DXGI_FORMAT backBufferFormat = DXGI_FORMAT_R8G8B8A8_UNORM, 
			DXGI_FORMAT depthStencilFormat = DXGI_FORMAT_D24_UNORM_S8_UINT);
		~RendererD3D11();

		ID3D11Device* GetDevice()			{ return _device;  };
		ID3D11DeviceContext* GetContext()	{ return _context; };

		void SetRenderTarget();
		void Clear(float r = 0.f, float g = 0.f, float b = 0.f);
		void Present();
		void Resize(int width, int height);
	private:
		EnumAdapters*			_enumAdapters;

		int						_width;
		int						_height;
		HWND					_hWnd;

		IDXGISwapChain*			_swapChain;
		ID3D11Device*			_device;
		ID3D11DeviceContext*	_context;

		DXGI_FORMAT				_backBufferFormat;
		DXGI_FORMAT				_depthStencilFormat;

		ID3D11RenderTargetView* _renderTargetView;
		ID3D11DepthStencilView* _depthStencilView;
		ID3D11Texture2D*		_depthStencilBuffer;

		ID3D11DepthStencilState* _depthStencilState;
		ID3D11RasterizerState*	 _rasterState;
	};
} //namespace

#endif