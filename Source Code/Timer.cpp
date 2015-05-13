#include "Timer.h"
#include <time.h>


Timer::Timer()
	{
		start = clock();
	}
Timer::Timer(clock_t e)
	{
		delay = e;  
	}

clock_t Timer::GetTime(){  return (clock()-start);	}

void Timer::setstart()
	{
		start = clock();
	}

void Timer:: setEndTime(clock_t d)
	{
		delay = d; 
	}

void Timer:: reset()
	{
		setstart();
	}

bool Timer:: TimerEnd()
	{
		if (clock() > start + delay)
		{
			setstart();
			return true;
		}

		return false;
	}

bool Timer:: TimeOver() const
{
 return ( clock()-start > delay ) ? true : false ;
}

Timer::~Timer()
{
	start = 0;
}

