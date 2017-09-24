#include "base/file_path.h"

static const char string_terminator = '\0';

static const char file_path_separator = '/';

static const char *current_directory = ".";
static const char *parent_directory = "..";

static const char extension_separator = '.';

bool file_path_is_separator(char c)
{
	return c == string_terminator;
}

