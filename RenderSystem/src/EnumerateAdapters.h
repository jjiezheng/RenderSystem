#ifndef _enumerateadapters_h_
#define _enumerateadapters_h_

#include "D3D11Util.h"
#include "Util.h"
#include <vector>

//---DisplayMode---
class DisplayMode
{
public:
	DisplayMode(DXGI_MODE_DESC displayMode) { _displayMode = displayMode; }
	~DisplayMode() {}

	u32						GetWidth()			  { return _displayMode.Width; }
	u32						GetHeight()		      { return _displayMode.Height; }
	u32						GetRefreshRateNum()   { return _displayMode.RefreshRate.Numerator; }
	u32						GetRefreshRateDenom() { return _displayMode.RefreshRate.Denominator; }
	DXGI_FORMAT					GetFormat()			  { return _displayMode.Format; }
	DXGI_MODE_SCALING			GetScaling()		  { return _displayMode.Scaling; }
	DXGI_MODE_SCANLINE_ORDER	GetScanlineOrdering() { return _displayMode.ScanlineOrdering; }
private:
	DXGI_MODE_DESC _displayMode;
};

//---Output---
class Output
{
public:
	Output(IDXGIOutput* output) { _output = output; }
	~Output() {}

	void ReleaseOuput()	{ ReleaseCOM(_output); _displayModes.clear(); }
	void GetDisplayModes();
private:
	u32			_numModes;
	IDXGIOutput*	_output;
	std::vector<DisplayMode> _displayModes;
};

//---Adapter---
class Adapter
{
public:
	Adapter(IDXGIAdapter* adapter) { _adapter = adapter; }
	~Adapter() {}

	void ReleaseAdapter() { ReleaseCOM(_adapter); }
	void ReleaseOutputs();
	void EnumerateOutputs();
private:
	IDXGIAdapter*		_adapter;
	std::vector<Output> _outputs;
public:
	DXGI_ADAPTER_DESC	adapterDesc;
};

//---EnumAdapters---
class EnumAdapters
{
public:
	EnumAdapters();
	~EnumAdapters();

	void EnumerateAdapters();
	void Release();
	Adapter* GetPrimaryAdapter();
private:
	std::vector<Adapter>  _adapters;
};

#endif