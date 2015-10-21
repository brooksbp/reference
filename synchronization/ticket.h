#ifndef SYNCHRONIZATION_TICKET_H
#define SYNCHRONIZATION_TICKET_H

#ifdef __cplusplus
extern "C" {
#endif

struct ticket_lock {
  int next_ticket;
  int now_serving;
};

void ticket_lock_acquire(struct ticket_lock *lock) {
  int my_ticket = __atomic_fetch_add(&lock->next_ticket, 1, __ATOMIC_RELAXED);
  while (__atomic_load_n(&lock->now_serving, __ATOMIC_RELAXED) != my_ticket)
    ;  // spin
  __atomic_thread_fence(__ATOMIC_ACQUIRE);
}

void ticket_lock_release(struct ticket_lock *lock) {
  int t = lock->now_serving + 1;
  __atomic_store_n(&lock->now_serving, t, __ATOMIC_RELEASE);
}

void ticket_lock_acquire_bo(struct ticket_lock *lock, int backoff) {
  int my_ticket = __atomic_fetch_add(&lock->next_ticket, 1, __ATOMIC_RELAXED);
  for (;;) {
    int ns = __atomic_load_n(&lock->now_serving, __ATOMIC_RELAXED);
    if (ns == my_ticket)
      break;
    for (int i = 0; i < (my_ticket - ns) * backoff; ++i)
      asm("");  // spin
  }
  __atomic_thread_fence(__ATOMIC_ACQUIRE);
}

#ifdef __cplusplus
}
#endif

#endif  // SYNCHRONIZATION_TICKET_H
