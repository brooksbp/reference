#ifndef BASE_FILE_PATH_H
#define BASE_FILE_PATH_H

#include "base/types.h"

#ifdef __cplusplus
extern "C" {
#endif

struct file_path {
	char *path;
};

bool file_path_is_separator(char c);

#ifdef __cplusplus
}
#endif

#endif /* BASE_FILE_PATH_H */
