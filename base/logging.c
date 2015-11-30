#include "base/time.h"

#include "base/logging.h"

#include <stdarg.h>
#include <stdio.h>
#include <sys/syscall.h>

const char* const log_severity_names[LOG_SEVERITY_NUM_SEVERITIES] = {
	"INFO", "WARNING", "ERROR", "FATAL"
};

void emit_msg(int severity, char *filename, int line, char *format, ...)
{
	struct time now = time_now();
	struct time_exploded exploded;

	time_local_explode(now, &exploded);

	fprintf(stderr, "%c %02d%02d %02d:%02d:%02d.%03d %05u %s:%d] ",
		log_severity_names[severity][0],
		exploded.month,
		exploded.day_of_month,
		exploded.hour,
		exploded.minute,
		exploded.second,
		exploded.millisecond,
		(unsigned int) syscall(SYS_gettid),
		filename, line);

	va_list args;
	va_start(args, format);
	vfprintf(stderr, format, args);
	va_end(args);

	fprintf(stderr, "\n");

	if (unlikely(severity == LOG_SEVERITY_FATAL))
		abort();
}
