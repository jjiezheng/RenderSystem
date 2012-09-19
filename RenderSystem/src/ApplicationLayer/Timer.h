#ifndef _timer_h_
#define _timer_h_

#include <windows.h>

class Timer 
{
public:
	Timer();
	~Timer();

	
	void Frame();
	float GetTime();
	float GetTotalElapsedTime();
private:
	bool Initialize();
private:
	INT64 _frequency;
	float _ticksPerMs;
	INT64 _startTime;
	float _frameTime;
	INT64 _begin;
	float _totalElapsedTimeSec;

};

#endif