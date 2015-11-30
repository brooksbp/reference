#include "base/synchronization/lock.h"

#include <stdlib.h>

#include "base/compiler.h"
#include "base/threading/platform_thread.h"
#include "gtest/gtest.h"

// Basic test to make sure that acquire()/release()/try() don't crash

struct basic_lock_data {
  struct lock lock;
  int acquired;
};

void *basic_lock_test_thread_main(void *arg) {
  struct basic_lock_data *data = (struct basic_lock_data *) arg;

  for (int i = 0; i < 10; i++) {
    lock_acquire(&data->lock);
    data->acquired++;
    lock_release(&data->lock);
  }
  for (int i = 0; i < 10; i++) {
    lock_acquire(&data->lock);
    data->acquired++;
    platform_thread_sleep_ms(rand() % 20);
    lock_release(&data->lock);
  }
  for (int i = 0; i < 10; i++) {
    if (lock_try(&data->lock)) {
      data->acquired++;
      platform_thread_sleep_ms(rand() % 20);
      lock_release(&data->lock);
    }
  }
  return NULL;
}

TEST(LockTest, Basic) {
  struct lock lock;
  struct basic_lock_data data;

  lock_ctor(&lock);

  data.acquired = 0;
  lock_ctor(&data.lock);

  platform_thread_handle_t handle;
  EXPECT_EQ(0, platform_thread_create(
      0, basic_lock_test_thread_main, &data, &handle));

  int acquired = 0;
  for (int i = 0; i < 5; i++) {
    lock_acquire(&lock);
    acquired++;
    lock_release(&lock);
  }
  for (int i = 0; i < 10; i++) {
    lock_acquire(&lock);
    acquired++;
    platform_thread_sleep_ms(rand() % 20);
    lock_release(&lock);
  }
  for (int i = 0; i < 10; i++) {
    if (lock_try(&lock)) {
      acquired++;
      platform_thread_sleep_ms(rand() % 20);
      lock_release(&lock);
    }
  }
  for (int i = 0; i < 5; i++) {
    lock_acquire(&lock);
    acquired++;
    platform_thread_sleep_ms(rand() % 20);
    lock_release(&lock);
  }

  platform_thread_join(handle);

  lock_dtor(&data.lock);
  lock_dtor(&lock);

  EXPECT_GE(acquired, 20);
  EXPECT_GE(data.acquired, 20);
}

// Tests that locks actually exclude

struct lock_mutex_data {
  struct lock lock;
  int *value;
};

void *lock_mutex_thread_main(void *arg) {
  struct lock_mutex_data *data = (struct lock_mutex_data *) arg;

  for (int i = 0; i < 40; i++) {
    lock_acquire(&data->lock);
    int v = *data->value;
    platform_thread_sleep_ms(rand() % 10);
    *data->value = v + 1;
    lock_release(&data->lock);
  }

  return NULL;
}

TEST(LockTest, MutexTwoThreads) {
  struct lock_mutex_data data;
  int value = 0;

  lock_ctor(&data.lock);
  data.value = &value;

  platform_thread_handle_t handle;
  EXPECT_EQ(0, platform_thread_create(
      0, lock_mutex_thread_main, &data, &handle));

  lock_mutex_thread_main((void *) &data);

  platform_thread_join(handle);

  EXPECT_EQ(2 * 40, value);

  lock_dtor(&data.lock);
}

TEST(LockTest, MutexFourThreads) {
  struct lock_mutex_data data;
  int value = 0;

  lock_ctor(&data.lock);
  data.value = &value;

  platform_thread_handle_t handle1, handle2, handle3;
  EXPECT_EQ(0, platform_thread_create(
      0, lock_mutex_thread_main, &data, &handle1));
  EXPECT_EQ(0, platform_thread_create(
      0, lock_mutex_thread_main, &data, &handle2));
  EXPECT_EQ(0, platform_thread_create(
      0, lock_mutex_thread_main, &data, &handle3));

  lock_mutex_thread_main((void *) &data);

  platform_thread_join(handle1);
  platform_thread_join(handle2);
  platform_thread_join(handle3);

  EXPECT_EQ(4 * 40, value);

  lock_dtor(&data.lock);
}
