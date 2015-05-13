#pragma once
#include <time.h>


class Timer
{
	clock_t start;
	clock_t delay; 
public:
	Timer(void);
	Timer(clock_t e);
	bool TimerEnd();
	bool TimeOver()  const;
	void setstart();
	void sleep(clock_t time);
	void setEndTime(clock_t time);
	clock_t GetTime();
	void reset();
	~Timer(void);
};
