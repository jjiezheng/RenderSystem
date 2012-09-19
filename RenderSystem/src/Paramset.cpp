#include "Paramset.h"
using namespace sturm;

template <class T> 
inline T* LookupPtr(std::vector<Param<T>>& vec, std::string key, int* size)
{
	for(u32 i = 0; i < vec.size(); ++i) {
		if(vec[i].key == key) {
			*size = vec[i].size;
			return vec[i].value;
		}
	}
	return NULL;
}

void ParamSet::AddInt(std::string key, int* val, int size) {
	_ints.push_back(Param<int>(key, val, size));
}
void ParamSet::AddFloat(std::string key, float* val, int size) {
	_floats.push_back(Param<float>(key, val, size));
}
void ParamSet::AddVecf4(std::string key, vecf4* val, int size) {
	_vecf4s.push_back(Param<vecf4>(key, val, size));
}
void ParamSet::AddVecf3(std::string key, vecf3* val, int size) {
	_vecf3s.push_back(Param<vecf3>(key, val, size));
}
void ParamSet::AddVecf2(std::string key, vecf2* val, int size) {
	_vecf2s.push_back(Param<vecf2>(key, val, size));
}
void ParamSet::AddMatrxif4(std::string key, matrixf4* val, int size) {
	_matrixf4s.push_back(Param<matrixf4>(key, val, size));
}
void ParamSet::AddMatrxif3(std::string key, matrixf3* val, int size) {
	_matrixf3s.push_back(Param<matrixf3>(key, val, size));
}

int* ParamSet::GetInt(std::string key, int* size) {
	return LookupPtr(_ints, key, size);
}
float* ParamSet::GetFloat(std::string key, int* size) {
	return LookupPtr(_floats, key, size);
}
vecf4* ParamSet::GetVecf4(std::string key, int* size) {
	return LookupPtr(_vecf4s, key, size);
}
vecf3* ParamSet::GetVecf3(std::string key, int* size) {
	return LookupPtr(_vecf3s, key, size);
}
vecf2* ParamSet::GetVecf2(std::string key, int* size) {
	return LookupPtr(_vecf2s, key, size);
}
matrixf4* ParamSet::GetMatrixf4(std::string key, int* size) {
	return LookupPtr(_matrixf4s, key, size);
}
matrixf3* ParamSet::GetMatrixf3(std::string key, int* size) {
	return LookupPtr(_matrixf3s, key, size);
}