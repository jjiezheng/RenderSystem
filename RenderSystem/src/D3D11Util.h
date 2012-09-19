#ifndef _d3dutil_h_
#define _d3dutil_h_

#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dx11.lib")

#include <d3d11.h>
#include <xnamath.h>
#include <Windows.h>


typedef XMFLOAT4	vecf4;
typedef XMFLOAT3	vecf3;
typedef XMFLOAT2	vecf2;
typedef XMFLOAT4X4	matrixf4;
typedef XMFLOAT3X3	matrixf3;

#define ReleaseCOM(x) { if(x){ x->Release();x = 0; } }
#define HRe(x) (x)
// void ReleaseCOM(IUnknown* com);
// bool HRe(HRESULT hret);

#endif