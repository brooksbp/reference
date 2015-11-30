#include "base/logging.h"

int main()
{
	LOG_INFO("Log message");

	int x = 0;
	CHECK(x == 0);

	return 0;
}
