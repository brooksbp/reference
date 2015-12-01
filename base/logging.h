#ifndef BASE_LOGGING_H
#define BASE_LOGGING_H

#include "base/compiler.h"
#include "base/types.h"

#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

#undef LOG_INFO
#undef LOG_WARNING
#undef LOG_ERROR
#undef LOG_FATAL
#undef LOG_IF
#undef CHECK
#undef DCHECK

#define LOG_INFO(format, ...) \
	emit_msg(LOG_SEVERITY_INFO, __FILENAME__, __LINE__, format, ##__VA_ARGS__)
#define LOG_WARNING(format, ...) \
	emit_msg(LOG_SEVERITY_WARNING, __FILENAME__, __LINE__, format, ##__VA_ARGS__)
#define LOG_ERROR(format, ...) \
	emit_msg(LOG_SEVERITY_ERROR, __FILENAME__, __LINE__, format, ##__VA_ARGS__)
#define LOG_FATAL(format, ...) \
	emit_msg(LOG_SEVERITY_FATAL, __FILENAME__, __LINE__, format, ##__VA_ARGS__)

#define LOG_IF(severity, condition, message)	\
	!(condition) ? (void) 0 : emit_msg(severity, __FILENAME__, __LINE__, message)

#define CHECK(condition) \
	LOG_IF(LOG_SEVERITY_FATAL, unlikely(!(condition)), "Check failed: " #condition)

#ifndef NDEBUG
#define DCHECK(condition) CHECK(condition)
#define DCHECK_EQ(c1, c2) CHECK((c1) == (c2))
#else
#define DCHECK(condition) (true) ? (void) 0 : CHECK(condition)
#define DCHECK_EQ(c1, c2) (true) ? (void) 0 : CHECK((c1) == (c2))
#endif

#if defined(NDEBUG)
#define NOTREACHED() LOG_ERROR("NOTREACHED() hit in %s", __FUNCTION__)
#else
#define NOTREACHED() DCHECK(false)
#endif

#define __FILENAME__ \
	(strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)

enum {
	LOG_SEVERITY_INFO = 0,
	LOG_SEVERITY_WARNING = 1,
	LOG_SEVERITY_ERROR = 2,
	LOG_SEVERITY_FATAL = 3,
	LOG_SEVERITY_NUM_SEVERITIES = 4,
};

void emit_msg(int severity, const char *filename, int line, const char *format, ...);

#ifdef __cplusplus
}
#endif

#endif /* BASE_LOGGING_H */
