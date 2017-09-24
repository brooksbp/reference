#ifndef BASE_STRING_UTIL_H
#define BASE_STRING_UTIL_H

#include "base/logging.h"
#include "base/types.h"

#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

static inline
char *string_append(const char *a, const char *b)
{	

}

static inline
bool is_empty(const char *str)
{
	return 0 == strlen(str);
}

static inline
char to_lower_ascii(char c)
{
	return (c >= 'A' && c <= 'Z') ? (c + ('a' - 'A')) : c;
}

char *string_copy_to_lower_ascii(const char *str);

static inline
char to_upper_ascii(char c)
{
	return (c >= 'a' && c <= 'z') ? (c + ('A' - 'a')) : c;
}

char *string_copy_to_upper_ascii(const char *str);

int string_compare_case_insensitive(const char *a, const char *b);

static inline
bool string_eq(const char *a, const char *b)
{
	return 0 == strcmp(a, b);
}

static inline
bool string_eq_case_insensitive(const char *a, const char *b)
{
	return 0 == string_compare_case_insensitive(a, b);
}

static inline
bool is_ascii_whitespace(char c)
{
	return c == ' ' || c == '\r' || c == '\n' || c == '\t';
}

static inline
bool is_ascii_alpha(char c)
{
	return ((c >= 'A') && (c <= 'Z')) || ((c >= 'a') && (c <= 'z'));
}

static inline
bool is_ascii_digit(char c)
{
	return c >= '0' && c <= '9';
}

static inline
bool is_hex_digit(char c)
{
	return (c >= '0' && c <= '9') ||
		(c >= 'A' && c <= 'F') ||
		(c >= 'a' && c <= 'f');
}

static inline
char hex_digit_to_int(char c)
{
	DCHECK(is_hex_digit(c));
	if (c >= '0' && c <= '9')
		return c - '0';
	if (c >= 'A' && c <= 'F')
		return c - 'A' + 10;
	if (c >= 'a' && c <= 'f')
		return c - 'a' + 10;
	return 0;
}

char *format_bytes(int64_t bytes);

#ifdef __cplusplus
}
#endif

#endif /* BASE_STRING_UTIL_H */
