#include "base/compile_time_macros.h"
#include "base/string_util.h"

char *string_copy_to_lower_ascii(const char *str)
{
	char *result = malloc(strlen(str) + 1);
	int i;
	for (i = 0; i < strlen(str); i++) {
		result[i] = to_lower_ascii(str[i]);
	}
	result[i] = '\0';
	return result;
}

char *string_copy_to_upper_ascii(const char *str)
{
	char *result = malloc(strlen(str) + 1);
	int i;
	for (i = 0; i < strlen(str); i++) {
		result[i] = to_upper_ascii(str[i]);
	}
	result[i] = '\0';
	return result;
}

int string_compare_case_insensitive(const char *a, const char *b)
{
	size_t i = 0;
	while (i < strlen(a) && i < strlen(b)) {
		if (to_lower_ascii(a[i]) < to_lower_ascii(b[i]))
			return -1;
		if (to_lower_ascii(a[i]) > to_lower_ascii(b[i]))
			return 1;
		i++;
	}

	if (strlen(a) == strlen(b))
		return 0;

	if (strlen(a) < strlen(b))
		return -1;
	return 1;
}

static const char * byte_dimension_strings[] = {
	" B",
	" kB",
	" MB",
	" GB",
	" TB",
	" PB"
};

char *format_bytes(int64_t bytes)
{
	double unit_amount = (double) bytes;
	size_t dimension = 0;
	const int kilo = 1024;
	while (unit_amount >= kilo &&
	       dimension < ARRAY_SIZE(byte_dimension_strings) - 1) {
		unit_amount /= kilo;
		dimension++;
	}

	char *buf = malloc(64);
	if (bytes != 0 && dimension > 0 && unit_amount < 100) {
		snprintf(buf, ARRAY_SIZE(buf), "%.1lf%s", unit_amount,
			 byte_dimension_strings[dimension]);
	} else {
		snprintf(buf, ARRAY_SIZE(buf), "%.0lf%s", unit_amount,
			 byte_dimension_strings[dimension]);
	}
	return buf;
}
