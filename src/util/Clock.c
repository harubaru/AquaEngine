#include <util/Clock.h>

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
	active_clock->diff = clock() - active_clock->start;
	active_clock->DeltaTime = 1000.0 * (active_clock->diff) / CLOCKS_PER_SEC;
	active_clock->DeltaTime *= 0.001;
}
