#ifndef _paramset_h_
#define _paramset_h_

#include "D3D11Util.h"
#include "Util.h"
#include <vector>

#include <map>
#include <string>

/*
	If a value is stored then is goes out of scope, could be bad.
*/

namespace sturm {

template <class T>
class Param {
public:
	template <class T>
	Param(std::string key, T* val, int size) : key(key), value(val), size(size) {};
	std::string key;
	T *value;
	int size;
};

class ParamSet {
public:
	void AddInt(std::string key, int* val, int size);
	void AddFloat(std::string key, float* val, int size);
	void AddVecf4(std::string key, vecf4* val, int size);
	void AddVecf3(std::string key, vecf3* val, int size);
	void AddVecf2(std::string key, vecf2* val, int size);
	void AddMatrxif4(std::string key, matrixf4* val, int size);
	void AddMatrxif3(std::string key, matrixf3* val, int size);

	int*		GetInt(std::string key, int* size);
	float*		GetFloat(std::string key, int* size);
	vecf4*		GetVecf4(std::string key, int* size);
	vecf3*		GetVecf3(std::string key, int* size);
	vecf2*		GetVecf2(std::string key, int* size);
	matrixf4*	GetMatrixf4(std::string key, int* size);
	matrixf3*	GetMatrixf3(std::string key, int* size);
private:
	std::vector<Param<int>>			_ints;
	std::vector<Param<float>>		_floats;
	std::vector<Param<vecf4>>		_vecf4s;
	std::vector<Param<vecf3>>		_vecf3s;
	std::vector<Param<vecf2>>		_vecf2s;
	std::vector<Param<matrixf4>>	_matrixf4s;
	std::vector<Param<matrixf3>>	_matrixf3s;
};

} //namespace

#endif