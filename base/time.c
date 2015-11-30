#include "base/time.h"

static uint64_t convert_timespec_to_nanos(struct timespec *ts)
{
	uint64_t result = ts->tv_sec;
	result *= NANOS_PER_SEC;
	result += ts->tv_nsec;
	return result;
}

static uint64_t clock_now(clockid_t clk_id)
{
	struct timespec ts;
	if (clock_gettime(clk_id, &ts) != 0) {
		LOG_ERROR("clock_gettime() failed");
		return 0;
	}
	return convert_timespec_to_nanos(&ts);
}



typedef time_t sys_time_t;

static sys_time_t sys_time_from_time_struct(
	struct tm *timestruct, bool is_local)
{
	if (is_local)
		return mktime(timestruct);
	else
		return timegm(timestruct);
}

static void sys_time_to_time_struct(
	sys_time_t t, struct tm *timestruct, bool is_local)
{
	if (is_local)
		localtime_r(&t, timestruct);
	else
		gmtime_r(&t, timestruct);
}

// -----------------------------------------------------------

struct time time_now(void)
{
	struct timeval tv;
	struct timezone tz = { 0, 0 };  /* UTC */
	struct time time = { 0 };

	if (gettimeofday(&tv, &tz) != 0) {
		LOG_ERROR("Could not determine time of day");
		return time;
	}
	time.us += tv.tv_sec * MICROS_PER_SEC;
	time.us += tv.tv_usec;
	return time;
}

static struct time from_exploded(bool is_local, struct time_exploded *exploded)
{
	struct time t;
	return t;
}

struct time time_from_utc_exploded(struct time_exploded *exploded)
{
	return from_exploded(false, exploded);
}

struct time time_from_local_exploded(struct time_exploded *exploded)
{
	return from_exploded(true, exploded);
}

static void explode(struct time time, bool is_local,
		    struct time_exploded *exploded)
{
	/*
	 * struct time stores times with microsecond resolution, but
	 * struct time_exploded only carries millisecond resolution,
	 * so begin by being lossy.
	 */
	int64_t microseconds = time.us;
	int64_t milliseconds;
	sys_time_t seconds;
	int millisecond;

	if (microseconds >= 0) {
		milliseconds = microseconds / MICROS_PER_MILLI;
		seconds = milliseconds / MILLIS_PER_SEC;
		millisecond = milliseconds % MILLIS_PER_SEC;
	} else {
		milliseconds = (microseconds - MICROS_PER_MILLI + 1) /
			MICROS_PER_MILLI;
		seconds = (milliseconds - MILLIS_PER_SEC + 1) /
			MILLIS_PER_SEC;
		millisecond = milliseconds % MILLIS_PER_SEC;
		if (millisecond < 0)
			millisecond += MILLIS_PER_SEC;
	}

	struct tm timestruct;
	sys_time_to_time_struct(seconds, &timestruct, is_local);

	exploded->year         = timestruct.tm_year + 1900;
	exploded->month        = timestruct.tm_mon + 1;
	exploded->day_of_week  = timestruct.tm_wday;
	exploded->day_of_month = timestruct.tm_mday;
	exploded->hour         = timestruct.tm_hour;
	exploded->minute       = timestruct.tm_min;
	exploded->second       = timestruct.tm_sec;
	exploded->millisecond  = millisecond;
}

void time_utc_explode(struct time time, struct time_exploded *exploded)
{
	explode(time, false, exploded);
}

void time_local_explode(struct time time, struct time_exploded *exploded)
{
	explode(time, true, exploded);
}

static bool is_in_range(int value, int lo, int high)
{
	return lo <= value && value <= high;
}

bool time_exploded_has_valid_values(struct time_exploded *exploded)
{
	return is_in_range(exploded->month, 1, 12) &&
		is_in_range(exploded->day_of_week, 0, 6) &&
		is_in_range(exploded->day_of_month, 1, 31) &&
		is_in_range(exploded->hour, 0, 23) &&
		is_in_range(exploded->minute, 0, 59) &&
		is_in_range(exploded->second, 0, 60) &&
		is_in_range(exploded->millisecond, 0, 999);
}

// ------------------------------------------------------------

time_ticks_t time_ticks_now(void)
{
	return (time_ticks_t) clock_now(CLOCK_MONOTONIC);
}

time_ticks_t thread_ticks_now(void)
{
	return (thread_ticks_t) clock_now(CLOCK_THREAD_CPUTIME_ID);
}







