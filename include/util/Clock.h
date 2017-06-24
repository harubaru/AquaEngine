#ifndef AQUAENGINE_UTIL_CLOCK_H
#define AQUAENGINE_UTIL_CLOCK_H

#ifdef __cplusplus
extern "C" {
#endif

#include <time.h>

struct Clock {
	clock_t start;
	clock_t diff;
	double DeltaTime;
};
typedef struct Clock Clock;

void Clock_Initialize(Clock* active_clock);
void Clock_TickBegin(Clock* active_clock);
void Clock_TickEnd(Clock* active_clock);

#ifdef __cplusplus
}
#endif

#endif
