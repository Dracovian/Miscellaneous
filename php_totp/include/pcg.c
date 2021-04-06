#include <time.h>
#include "pcg.h"

#if __STDC_VERSION__ >= 201112L && !defined(__STDC_NO_ATOMICS__)
	#include <stdatomic.h>

	#define SPINLOCK_DECLARE(mutex) volatile int mutex = ATOMIC_FLAG_INIT
	#define SPINLOCK_LOCK(mutex)    do {} while (atomic_flag_test_and_set(&mutex))
	#define SPINLOCK_UNLOCK(mutex)  atomic_flag_clear(&mutex)

#elif __GNUC__
	#define SPINLOCK_DECLARE(mutex) volatile int mutex = 0
	#define SPINLOCK_LOCK(mutex)    do {} while (__sync_lock_test_and_set(&mutex, 1))
	#define SPINLOCK_UNLOCK(mutex)  __sync_lock_release(&mutex)

#else
	#warning No implementation of atomics provided, no thread safety guaranteed.

	#define SPINLOCK_DECLARE(mutex) volatile int mutex = 0
	#define SPINLOCK_LOCK(mutex)    do { while (mutex == 1) {} mutex = 1; } while (0)
	#define SPINLOCK_UNLOCK(mutex)  mutex = 0
#endif

void pcg_step(random_t *rand) {
	rand->state = rand->state * PCG64_MULTIPLIER + rand->increment;
}

void pcg_srandom(random_t *rand, i64 seq, i64 inc) {
	rand->state = 0;
	rand->increment = (seq << 1) | 1;
	pcg_step(rand);

	rand->state += inc;
	pcg_step(rand);
}

i64 pcg_rotate(i64 val, i64 rotation) {
	return (val >> rotation) | (val << ((- rotation) & 63));
}

i64 pcg_output(i64 state) {
	return pcg_rotate((state >> 32) ^ state, state >> 59);
}

i64 pcg_random(random_t *rand) {
	pcg_step(rand);
	return pcg_output(rand->state);
}

i64 pcg_bounded(random_t *rand, i64 min, i64 max) {
	i64 threshold = -max % max;

	for (;;) {
		i64 r = pcg_random(rand);
		if (r >= threshold) return (r % max) + min;
	}
}

void entropy_getbytes(void *destination, long size) {
	static SPINLOCK_DECLARE(mutex);
	SPINLOCK_LOCK(mutex);

	static int init = 0;
	static random_t rand;

	if (init == 0) {
		int tmpvar;

		pcg_srandom(&rand, (i64) &tmpvar, (i64) (time(NULL) ^ (i64) &entropy_getbytes));
		init++;
	}

	char *dest = (char *) destination;
	for (long i = 0; i < size; ++i)
		dest[i] = (char) pcg_random(&rand);

	SPINLOCK_UNLOCK(mutex);
}
