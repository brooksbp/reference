#include "base/logging.h"
#include "base/sys_info.h"

static int64 amount_of_memory(int pages_name)
{
	long pages = sysconf(pages_name);
	long page_size = sysconf(_SC_PAGESIZE);
	if (pages == -1 || page_size == -1) {
		NOTREACHED();
		return 0;
	}
	return (int64)(pages * page_size);
}

int64 sys_info_amount_of_physical_memory(void)
{
	return amount_of_memory(_SC_PHYS_PAGES);
}

int64 sys_info_amount_of_available_physical_memory(void)
{
	return amount_of_memory(_SC_AVPHYS_PAGES);
}
