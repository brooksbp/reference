#include "base/eintr_wrapper.h"
#include "base/file.h"
#include "base/logging.h"

#include <fcntl.h>
#include <sys/stat.h>

static int call_fstat(int fd, struct stat64 *sb)
{
	return fstat64(fd, sb);
}

static bool is_open_append(int file)
{
	return (fcntl(file, F_GETFL) & O_APPEND) != 0;
}

static int call_ftruncate(int file, int64_t length)
{
	return HANDLE_EINTR(ftruncate(file, length));
}

static int os_error_to_file_error(int saved_errno)
{
	switch (saved_errno) {
	case EACCES:
	case EISDIR:
	case EROFS:
	case EPERM:
		return FILE_ERROR_ACCESS_DENIED;
	case EBUSY:
	case ETXTBSY:
		return FILE_ERROR_IN_USE;
	case EEXIST:
		return FILE_ERROR_EXISTS;
	case EIO:
		return FILE_ERROR_IO;
	case ENOENT:
		return FILE_ERROR_NOT_FOUND;
	case EMFILE:
		return FILE_ERROR_TOO_MANY_OPENED;
	case ENOMEM:
		return FILE_ERROR_NO_MEMORY;
	case ENOSPC:
		return FILE_ERROR_NO_SPACE;
	case ENOTDIR:
		return FILE_ERROR_NOT_A_DIRECTORY;
	default:
		return FILE_ERROR_FAILED;
	}
}

char *file_error_to_string(int error)
{
	switch (error) {
	case FILE_OK:
		return "FILE_OK";
	case FILE_ERROR_FAILED:
		return "FILE_ERROR_FAILED";
	case FILE_ERROR_IN_USE:
		return "FILE_ERROR_IN_USE";
	case FILE_ERROR_EXISTS:
		return "FILE_ERROR_EXISTS";
	case FILE_ERROR_NOT_FOUND:
		return "FILE_ERROR_NOT_FOUND";
	case FILE_ERROR_ACCESS_DENIED:
		return "FILE_ERROR_ACCESS_DENIED";
	case FILE_ERROR_TOO_MANY_OPENED:
		return "FILE_ERROR_TOO_MANY_OPENED";
	case FILE_ERROR_NO_MEMORY:
		return "FILE_ERROR_NO_MEMORY";
	case FILE_ERROR_NO_SPACE:
		return "FILE_ERROR_NO_SPACE";
	case FILE_ERROR_NOT_A_DIRECTORY:
		return "FILE_ERROR_NOT_A_DIRECTORY";
	case FILE_ERROR_INVALID_OPERATION:
		return "FILE_ERROR_INVALID_OPERATION";
	case FILE_ERROR_SECURITY:
		return "FILE_ERROR_SECURITY";
	case FILE_ERROR_ABORT:
		return "FILE_ERROR_ABORT";
	case FILE_ERROR_NOT_A_FILE:
		return "FILE_ERROR_NOT_A_FILE";
	case FILE_ERROR_NOT_EMPTY:
		return "FILE_ERROR_NOT_EMPTY";
	case FILE_ERROR_INVALID_URL:
		return "FILE_ERROR_INVALID_URL";
	case FILE_ERROR_IO:
		return "FILE_ERROR_IO";
	case FILE_ERROR_MAX:
		break;
	}

	NOTREACHED();
	return "";
}

void file_close(struct file *file)
{
	if (!file_is_valid(file))
		return;

	close(file->fd);
	file->fd = -1;
}

int file_read(struct file *file, uint64_t offset, char *data, int size)
{
	DCHECK(file_is_valid(file));
	if (size < 0)
		return -1;

	int bytes_read = 0;
	int rv;
	do {
		rv = HANDLE_EINTR(pread(file->fd, data + bytes_read,
					size - bytes_read, offset + bytes_read));
		if (rv <= 0)
			break;

		bytes_read += rv;
	} while (bytes_read < size);

	return bytes_read ? bytes_read : rv;
}

int file_write(struct file *file, uint64_t offset, const char *data, int size)
{
	if (is_open_append(file->fd))
		return file_write_at_current_pos(file, data, size);

	DCHECK(file_is_valid(file));
	if (size < 0)
		return -1;

	int bytes_written = 0;
	int rv;
	do {
		rv = HANDLE_EINTR(pwrite(file->fd, data + bytes_written,
					 size - bytes_written,
					 offset + bytes_written));
		if (rv <= 0)
			break;

		bytes_written += rv;
	} while (bytes_written < size);

	return bytes_written ? bytes_written : rv;
}

int file_write_at_current_pos(struct file *file, const char *data, int size)
{
	DCHECK(file_is_valid(file));
	if (size < 0)
		return -1;

	int bytes_written = 0;
	int rv;
	do {
		rv = HANDLE_EINTR(write(file->fd, data + bytes_written,
					size - bytes_written));
		if (rv <= 0)
			break;

		bytes_written += rv;
	} while (bytes_written < size);

	return bytes_written ? bytes_written : rv;
}

int64_t file_get_length(struct file *file)
{
	DCHECK(file_is_valid(file));

	struct stat64 file_info;
	if (call_fstat(file->fd, &file_info))
		return -1;

	return file_info.st_size;
}

bool file_set_length(struct file *file, int64_t length)
{
	DCHECK(file_is_valid(file));

	return !call_ftruncate(file->fd, length);
}

void file_init(struct file *file, const char *file_path, uint32_t flags)
{
	DCHECK(!file_is_valid(file));

	file->path = file_path;

	int open_flags = 0;
	if (flags & FLAG_CREATE)
		open_flags = O_CREAT | O_EXCL;

	file->created = false;

	if (flags & FLAG_CREATE_ALWAYS) {
		DCHECK(!open_flags);
		DCHECK(flags & FLAG_WRITE);
		open_flags = O_CREAT | O_TRUNC;
	}

	if (flags & FLAG_OPEN_TRUNCATED) {
		DCHECK(!open_flags);
		DCHECK(flags & FLAG_WRITE);
		open_flags = O_TRUNC;
	}

	if (!open_flags && !(flags & FLAG_OPEN) && !(flags & FLAG_OPEN_ALWAYS)) {
		NOTREACHED();
		errno = EOPNOTSUPP;
		file->error_details = FILE_ERROR_FAILED;
		return;
	}

	if (flags & FLAG_WRITE && flags & FLAG_READ) {
		open_flags |= O_RDWR;
	} else if (flags & FLAG_WRITE) {
		open_flags |= O_WRONLY;
	} else if (!(flags & FLAG_READ) &&
		   !(flags & FLAG_APPEND) &&
		   !(flags & FLAG_OPEN_ALWAYS)) {
		NOTREACHED();
	}

	if (flags & FLAG_APPEND && flags & FLAG_READ)
		open_flags |= O_APPEND | O_RDWR;
	else if (flags & FLAG_APPEND)
		open_flags |= O_APPEND | O_WRONLY;

	int mode = S_IRUSR | S_IWUSR;

	int descriptor = HANDLE_EINTR(open(file->path, open_flags, mode));

	/* TODO */

	if (descriptor < 0) {
		file->error_details = os_error_to_file_error(errno);
		return;
	}

	if (flags & (FLAG_CREATE_ALWAYS | FLAG_CREATE))
		file->created = true;

	if (flags & FLAG_DELETE_ON_CLOSE)
		unlink(file->path);

	file->error_details = FILE_OK;
	file->fd = descriptor;
}

bool file_do_flush(struct file *file)
{
	DCHECK(file_is_valid(file));
	return !HANDLE_EINTR(fdatasync(file->fd));
}
