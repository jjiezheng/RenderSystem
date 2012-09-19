#include "EnumerateAdapters.h"

EnumAdapters::EnumAdapters()
{}

EnumAdapters::~EnumAdapters()
{}

/** 
	Enumerate through each adapter and its outputs
	adding references to the adapters and outputs
	@see EnumerateOutputs
**/
void EnumAdapters::EnumerateAdapters()
{
	u32 i = 0;
	IDXGIFactory* factory;
	IDXGIAdapter* padapter;

	HRe(CreateDXGIFactory(__uuidof(IDXGIFactory), (void**)&factory));
	while(factory->EnumAdapters(i, &padapter) != DXGI_ERROR_NOT_FOUND)
	{
		Adapter adapter(padapter);
		_adapters.push_back(adapter);
		i++;
	}

	std::vector<Adapter>::iterator it;
	for(it = _adapters.begin(); it != _adapters.end(); it++)
	{
		it->EnumerateOutputs();
	}

	factory->Release();
	factory = 0;
}

/** 
	Release the COM that each Adapter Class holds
	@see ReleaseOutputs
	@see ReleaseAdapter
**/
void EnumAdapters::Release()
{
	std::vector<Adapter>::iterator it;
	for(it = _adapters.begin(); it != _adapters.end(); it++)
	{
		it->ReleaseOutputs();
		it->ReleaseAdapter();
	}
	_adapters.clear();
}

Adapter* EnumAdapters::GetPrimaryAdapter() {
	return &_adapters[0];
}

/**
	Add a reference to each output for the adapter
	then get the all possible DisplayModes for the output
	@see GetDisplayMode
**/
void Adapter::EnumerateOutputs()
{
	u32 i = 0;
	IDXGIOutput* poutput;
	
	HRe(_adapter->GetDesc(&adapterDesc));

	while(_adapter->EnumOutputs(i, &poutput) != DXGI_ERROR_NOT_FOUND)
	{
		Output output(poutput);
		_outputs.push_back(output);
		i++;
	}

	std::vector<Output>::iterator it;
	for(it = _outputs.begin(); it != _outputs.end(); it++)
	{
		it->GetDisplayModes();
	}
}

/** 
	Release the COM that each output holds
	@see ReleaseOutput
**/
void Adapter::ReleaseOutputs()
{
	std::vector<Output>::iterator it;
	for(it = _outputs.begin(); it != _outputs.end(); it++)
	{
		it->ReleaseOuput();
	}
	_outputs.clear();
}

/** 
	Find the number of displayModes for the given output.
	For each display mode, creates a DisplayMode object 
	and pushes it onto a vector.
**/
void Output::GetDisplayModes()
{
	HRe(_output->GetDisplayModeList(DXGI_FORMAT_B8G8R8A8_UNORM, DXGI_ENUM_MODES_INTERLACED,
		&_numModes, NULL));
	
	DXGI_MODE_DESC* displayModes = new DXGI_MODE_DESC[_numModes];
	if(displayModes == NULL) { OutputDebugString(L"Boom"); }

	HRe(_output->GetDisplayModeList(DXGI_FORMAT_B8G8R8A8_UNORM, DXGI_ENUM_MODES_INTERLACED,
		&_numModes, displayModes));

	for(u32 i = 0; i < _numModes; i++)
	{
		DisplayMode mode(displayModes[i]);
		_displayModes.push_back(mode);
	}

	delete [] displayModes;
	displayModes = 0;

}