#ifndef BASE_SYNCHRONIZATION_MCS_H
#define BASE_SYNCHRONIZATION_MCS_H

struct qnode {
	struct qnode *next;
	char waiting;
};

struct mcs_lock {
	struct qnode *tail;
};

static inline void mcs_lock_acquire(struct mcs_lock *lock, struct qnode *p)
{
	p->next = NULL;
	p->waiting = 1;
	struct qnode *prev =
		__atomic_exchange_n(&lock->tail, p, __ATOMIC_RELEASE);
	if (prev != NULL) {
		__atomic_store_n(&prev->next, p, __ATOMIC_RELAXED);
		while (__atomic_load_n(&p->waiting, __ATOMIC_RELAXED))
			;  // spin
	}
	__atomic_thread_fence(__ATOMIC_ACQUIRE);
}

static inline void mcs_lock_release(struct mcs_lock *lock, struct qnode *p)
{
	__atomic_thread_fence(__ATOMIC_RELEASE);
	struct qnode *succ = __atomic_load_n(&p->next, __ATOMIC_RELAXED);
	if (succ == NULL) {
		struct qnode *q = p;
		if (__atomic_compare_exchange_n(
			    &lock->tail, &q, NULL, 0,
			    __ATOMIC_ACQUIRE, __ATOMIC_RELAXED))
			return;
		do
			succ = __atomic_load_n(&p->next, __ATOMIC_RELAXED);
		while (succ == NULL);
	}
	__atomic_store_n(&succ->waiting, 0, __ATOMIC_RELAXED);
}

#endif /* BASE_SYNCHRONIZATION_MCS_H */
