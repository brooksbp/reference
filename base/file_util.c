#include "base/file_util.h"

#include <string.h>

static char *temp_file_name(void)
{
	static const char *__temp_file_name = ".reference.XXXXXX";
	return strcpy(malloc(sizeof(__temp_file_name + 1)), __temp_file_name);
}

/*
 * Creates an opens a temporary file in |directory|, returning the
 * file descriptor. |path| is set to the temporary file path.
 */
static int create_and_open_fd_for_temporary_file(struct file_path *directory,
						 struct file_path *path)
{
	
}
