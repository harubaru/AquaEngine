#include <util/Timer.h>

void Timer::Start()
{
	start = std::chrono::high_resolution_clock::now();
}

void Timer::End()
{
	end = std::chrono::high_resolution_clock::now();
}

double Timer::GetDuration()
{
	std::chrono::duration<double> duration = std::chrono::duration_cast<std::chrono::duration<double>>(end - start);
	return duration.count();
}

