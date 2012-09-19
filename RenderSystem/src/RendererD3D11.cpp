#include "RendererD3D11.h"
#include "RenderState.h"
using namespace sturm;


RendererD3D11::RendererD3D11(int width, int height, HWND hWnd, 
	DXGI_FORMAT backBufferFormat /* = DXGI_FORMAT_R8G8B8A8_UNORM */,
	DXGI_FORMAT depthStencilFormat /* = DXGI_FORMAT_D24_UNORM_S8_UINT */) 
: _renderTargetView(0), _depthStencilView(0), _depthStencilBuffer(0) {

	DXGI_SWAP_CHAIN_DESC scd;
	D3D_FEATURE_LEVEL featureLevel;
	UINT createDeviceFlags = 0;
	D3D11_DEPTH_STENCIL_DESC dsd;

	_enumAdapters = new EnumAdapters();
	_enumAdapters->EnumerateAdapters();

	_width				= width;
	_height				= height;
	_hWnd				= hWnd;
	_backBufferFormat	= backBufferFormat;
	_depthStencilFormat = depthStencilFormat;

	//Create swap chain
	ZeroMemory(&scd, sizeof(scd));
	scd.BufferCount							= 1;
	scd.BufferDesc.Format					= backBufferFormat;
	scd.BufferDesc.Width					= _width;
	scd.BufferDesc.Height					= _height;
	scd.BufferDesc.RefreshRate.Numerator	= 0;
	scd.BufferDesc.RefreshRate.Denominator	= 1;
	scd.BufferDesc.ScanlineOrdering			= DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	scd.BufferDesc.Scaling					= DXGI_MODE_SCALING_UNSPECIFIED;
	//Turn off multi-sampling
	scd.SampleDesc.Count					= 1;
	scd.SampleDesc.Quality					= 0;
	scd.BufferUsage							= DXGI_USAGE_RENDER_TARGET_OUTPUT;
	scd.OutputWindow						= hWnd;
	scd.SwapEffect							= DXGI_SWAP_EFFECT_DISCARD;
	scd.Flags								= 0;
	scd.Windowed							= true;

	featureLevel = D3D_FEATURE_LEVEL_11_0;

#if defined(DEBUG) || defined(_DEBUG)
	createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

	//Create swapchain, device, and device context
	HRe(D3D11CreateDeviceAndSwapChain(0, D3D_DRIVER_TYPE_HARDWARE, 0, createDeviceFlags, &featureLevel, 1, 
		D3D11_SDK_VERSION, &scd, &_swapChain, &_device, NULL, &_context));

	Resize(_width, _height);

	ZeroMemory(&dsd, sizeof(dsd));

	dsd.DepthEnable = true;
	dsd.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	dsd.DepthFunc = D3D11_COMPARISON_LESS;
	dsd.StencilEnable = true;
	dsd.StencilReadMask = 0xFF;
	dsd.StencilWriteMask = 0xFF;
	dsd.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	dsd.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;
	dsd.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	dsd.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;
	dsd.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	dsd.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_DECR;
	dsd.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	dsd.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

	HRe(_device->CreateDepthStencilState(&dsd, &_depthStencilState));

	_context->OMSetDepthStencilState(_depthStencilState, 1);

	D3D11_RASTERIZER_DESC rd;
	rd.AntialiasedLineEnable = false;
	rd.CullMode = D3D11_CULL_BACK;
	rd.DepthBias = 0;
	rd.DepthBiasClamp = 0.0f;
	rd.FillMode = D3D11_FILL_SOLID;
	rd.FrontCounterClockwise = false;
	rd.MultisampleEnable = false;
	rd.ScissorEnable = false;
	rd.SlopeScaledDepthBias = 0.0f;

	HRe(_device->CreateRasterizerState(&rd, &_rasterState));

	_context->RSSetState(_rasterState);
}

RendererD3D11::~RendererD3D11() {
	ReleaseCOM(_swapChain);
	ReleaseCOM(_device);
	ReleaseCOM(_context);
	ReleaseCOM(_renderTargetView);
	ReleaseCOM(_depthStencilBuffer);
	ReleaseCOM(_depthStencilView);
}


void RendererD3D11::Resize(int width, int height) {
	ReleaseCOM(_renderTargetView);
	ReleaseCOM(_depthStencilView);
	ReleaseCOM(_depthStencilBuffer);

	ID3D11Texture2D* pBackbuffer;
	D3D11_TEXTURE2D_DESC t2d;
	D3D11_DEPTH_STENCIL_VIEW_DESC dsvd;

	_width = width;
	_height = height;

	//create renderTarget
	_swapChain->ResizeBuffers(1, _width, _height, _backBufferFormat, 0);
	_swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackbuffer);
	_device->CreateRenderTargetView(pBackbuffer, 0, &_renderTargetView);

	//create depthstencil buffer
	ZeroMemory(&t2d, sizeof(t2d));
	t2d.Width				= _width;
	t2d.Height				= _height;
	t2d.MipLevels			= 1;
	t2d.ArraySize			= 1;
	t2d.Format				= _depthStencilFormat;
	t2d.SampleDesc.Count	= 1;
	t2d.SampleDesc.Quality	= 0;
	t2d.Usage				= D3D11_USAGE_DEFAULT;
	t2d.BindFlags			= D3D11_BIND_DEPTH_STENCIL;
	t2d.CPUAccessFlags		= 0;
	t2d.MiscFlags			= 0;

	HRe(_device->CreateTexture2D(&t2d, 0, &_depthStencilBuffer));

	//create depth stencil view

	//check if depthStencil buffer exists
	if(!_depthStencilBuffer) return;

	ZeroMemory(&dsvd, sizeof(dsvd));
	dsvd.Format				= _depthStencilFormat;
	dsvd.ViewDimension		= D3D11_DSV_DIMENSION_TEXTURE2D;
	dsvd.Texture2D.MipSlice = 0;

	HRe(_device->CreateDepthStencilView(_depthStencilBuffer, &dsvd, &_depthStencilView));

	//set render target
	_context->OMSetRenderTargets(1, &_renderTargetView, _depthStencilView);

	//viewport?
}

void RendererD3D11::SetRenderTarget() {

}

void RendererD3D11::Clear(float r /* = 0.f */, float g /* = 0.f */, float b /* = 0.f */) {
	float color[4]; //clear color
	color[0] = r; color[1] = g; color[2] = b; color[3] = 1.f;

	_context->ClearRenderTargetView(_renderTargetView, color);
	_context->ClearDepthStencilView(_depthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);
}

void RendererD3D11::Present() {
	_swapChain->Present(0,0); //Vsync disabled
}

