#include "base/threading/platform_thread.h"
#include "gtest/gtest.h"

struct trivial_thread {
  int did_run;
};

void *trivial_thread_func(void *arg) {
  struct trivial_thread *thread = (struct trivial_thread *) arg;

  thread->did_run = 1;

  return NULL;
}

TEST(platform_thread_test, trivial) {
  struct trivial_thread thread;
  platform_thread_handle_t handle;

  thread.did_run = 0;
  EXPECT_EQ(0, thread.did_run);
  EXPECT_EQ(0, platform_thread_create(
      0, trivial_thread_func, &thread, &handle));
  platform_thread_join(handle);
  EXPECT_EQ(1, thread.did_run);
}
