#ifndef BASE_FILE_H
#define BASE_FILE_H

#include "base/types.h"

#ifdef __cplusplus
extern "C" {
#endif

static inline
bool fd_is_valid(int fd)
{
	return fd != -1;
}

enum {
	FLAG_OPEN = 1 << 0,           /* Opens a file, only if it exists. */
	FLAG_CREATE = 1 << 1,         /* Creates a new file, only if it does not
				       * already exist. */
	FLAG_OPEN_ALWAYS = 1 << 2,    /* May create a new file. */
	FLAG_CREATE_ALWAYS = 1 << 3,  /* May overwrite an old file. */
	FLAG_OPEN_TRUNCATED = 1 << 4, /* Opens a file and truncates it, only if
				       * it exists. */
	FLAG_READ = 1 << 5,
	FLAG_WRITE = 1 << 6,
	FLAG_APPEND = 1 << 7,

	FLAG_ASYNC = 1 << 10,

	FLAG_DELETE_ON_CLOSE = 1 << 13,
};

enum {
	FILE_OK = 0,
	FILE_ERROR_FAILED = -1,
	FILE_ERROR_IN_USE = -2,
	FILE_ERROR_EXISTS = -3,
	FILE_ERROR_NOT_FOUND = -4,
	FILE_ERROR_ACCESS_DENIED = -5,
	FILE_ERROR_TOO_MANY_OPENED = -6,
	FILE_ERROR_NO_MEMORY = -7,
	FILE_ERROR_NO_SPACE = -8,
	FILE_ERROR_NOT_A_DIRECTORY = -9,
	FILE_ERROR_INVALID_OPERATION = -10,
	FILE_ERROR_SECURITY = -11,
	FILE_ERROR_ABORT = -12,
	FILE_ERROR_NOT_A_FILE = -13,
	FILE_ERROR_NOT_EMPTY = -14,
	FILE_ERROR_INVALID_URL = -15,
	FILE_ERROR_IO = -16,
	FILE_ERROR_MAX = -17,
};

char *file_error_to_string(int error);

struct file {
	const char *path;
	int fd;
	bool created;
	int error_details;
};

static inline
bool file_is_valid(struct file *file)
{
	return fd_is_valid(file->fd);
}

void file_close(struct file *file);
int file_read(struct file *file, uint64_t offset, char *data, int size);
int file_write(struct file *file, uint64_t offset, const char *data, int size);
int file_write_at_current_pos(struct file *file, const char *data, int size);
int64_t file_get_length(struct file *file);
bool file_set_length(struct file *file, int64_t length);
void file_init(struct file *file, const char *file_path, uint32_t flags);
bool file_do_flush(struct file *file);

#ifdef __cplusplus
}
#endif

#endif /* BASE_FILE_H */
