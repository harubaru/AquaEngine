#include <util/Clock.h>

#if defined(_WIN32)

static double clock_frequency = 0.0;

void Clock_Initialize(Clock* active_clock)
{
	LARGE_INTEGER i;
	QueryPerformanceFrequency(&i);
	clock_frequency = (double)i.QuadPart / 1000.0;
	active_clock->DeltaTime = 0.0;

}

void Clock_TickBegin(Clock* active_clock)
{
	LARGE_INTEGER i;
	QueryPerformanceCounter(&i);
	active_clock->start = i.QuadPart;
}

void Clock_TickEnd(Clock* active_clock)
{
	LARGE_INTEGER i;
	QueryPerformanceCounter(&i);
	active_clock->DeltaTime = 0.001 * (double)(i.QuadPart - active_clock->start) / clock_frequency;
}

void Clock_Delay(unsigned int ms)
{
	Sleep(ms);
}

#elif defined(__linux__)

void Clock_Initialize(Clock* active_clock)
{
	active_clock->DeltaTime = 0.0; 
}

void Clock_TickBegin(Clock* active_clock)
{
	gettimeofday(&active_clock->start, NULL);
}

void Clock_TickEnd(Clock* active_clock)
{
	struct timeval end;
	gettimeofday(&end, NULL);

	active_clock->DeltaTime = (double)((end.tv_sec - active_clock->start.tv_sec) * 1000 + (end.tv_usec - active_clock->start.tv_usec) / 1000);
	active_clock->DeltaTime *= 0.001;
}

void Clock_Delay(unsigned int ms)
{
	struct timespec elapsed, tv;

	elapsed.tv_sec = ms / 1000;
	elapsed.tv_nsec = (ms % 1000) * 1000000;
	
	tv.tv_sec = elapsed.tv_sec;
	tv.tv_nsec = elapsed.tv_nsec;

	nanosleep(&tv, &elapsed);
}


#else
void Clock_Initialize(Clock* active_clock)
{
	active_clock->DeltaTime = 0;
}

void Clock_TickBegin(Clock* active_clock)
{
	active_clock->start = clock();
}

void Clock_TickEnd(Clock* active_clock)
{
	clock_t diff = clock() - active_clock->start;
	active_clock->DeltaTime = diff / CLOCKS_PER_SEC;
}

void Clock_Delay(unsigned int ms)
{
	clock_t start = clock();

	while (clock() < start + ms);	
}

#endif
