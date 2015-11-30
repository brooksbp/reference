#ifndef BASE_TIME_H
#define BASE_TIME_H

#include "base/types.h"

#include <time.h>
#include <sys/time.h>

#if defined(__cplusplus)
extern "C" {
#endif

#define MILLIS_PER_SEC 1000

#define MICROS_PER_SEC (MICROS_PER_MILLI * MILLIS_PER_SEC)
#define MICROS_PER_MILLI 1000

#define NANOS_PER_SEC (NANOS_PER_MILLI * MILLIS_PER_SEC)
#define NANOS_PER_MILLI (NANOS_PER_MICRO * MICROS_PER_MILLI)
#define NANOS_PER_MICRO 1000

struct time {
	int64_t us;
};

struct time_exploded {
	int year;
	int month;
	int day_of_week;
	int day_of_month;
	int hour;
	int minute;
	int second;
	int millisecond;
};

struct time time_now(void);
struct time time_from_utc_exploded(struct time_exploded *exploded);
struct time time_from_local_exploded(struct time_exploded *exploded);
void time_utc_explode(struct time time, struct time_exploded *exploded);
void time_local_explode(struct time time, struct time_exploded *exploded);
bool time_exploded_has_valid_values(struct time_exploded *exploded);

typedef uint64_t time_ticks_t; /* in nanoseconds */

typedef uint64_t thread_ticks_t; /* in nanoseconds */



time_ticks_t time_ticks_now(void);

thread_ticks_t thread_ticks_now(void);

#if defined(__cplusplus)
}
#endif

#endif /* BASE_TIME_H */



