#include "timer.h"

Timer::Timer() {
	Initialize();
}

Timer::~Timer() {

}

bool Timer::Initialize() {
	//check if we support high performance timers
	QueryPerformanceFrequency((LARGE_INTEGER*)&_frequency);
	if(_frequency == 0) {
		return false;
	}

	_ticksPerMs = (float)(_frequency / 1000);

	QueryPerformanceCounter((LARGE_INTEGER*)&_startTime);
	_begin = _startTime;
	return true;
}

void Timer::Frame() {
	INT64 currentTime;
	float timeDifference;

	QueryPerformanceCounter((LARGE_INTEGER*)& currentTime);

	timeDifference = (float)(currentTime - _startTime);

	_frameTime = timeDifference / _ticksPerMs;

	_startTime = currentTime;

	return;
}

float Timer::GetTime() { return _frameTime; }

float Timer::GetTotalElapsedTime() { 
	INT64 currentTime;
	float timeDifference;

	QueryPerformanceCounter((LARGE_INTEGER*)& currentTime);
	timeDifference = (float)(currentTime - _begin);
	_totalElapsedTimeSec = timeDifference / _ticksPerMs / 1000.f;
	return _totalElapsedTimeSec;
}