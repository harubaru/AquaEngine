#ifndef AQUAGL_TIMER_H
#define AQUAGL_TIMER_H

#include <chrono>

class Timer {
private:
	std::chrono::high_resolution_clock::time_point start, end;
public:
	Timer() {}

	void Start();
	void End();

	double GetDuration();
};

#endif

