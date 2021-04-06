#ifndef __LINKCRYPT_RANDOM_H
#error Do not include this header file directly. Use random.h instead.
#endif

#ifndef __LINKCRYPT_RANDOM_SPINLOCK_H
#define __LINKCRYPT_RANDOM_SPINLOCK_H
#include <stdint.h>
#include <time.h>

#if defined(__unix__) || defined(__unix) || defined(__MACH__)
#include <fcntl.h>
#include <unistd.h>

#define HAVE_DEV_RANDOM 1
#endif

#if __STDC_VERSION__ >= 201112L && !__STDC_NO_ATOMICS__
    #include <stdatomic.h>
    #define SPINLOCK_DECLARE(mutex) atomic_flag mutex = ATOMIC_FLAG_INIT
    #define SPINLOCK_LOCK(mutex) do {} while (atomic_flag_test_and_set(&mutex))
    #define SPINLOCK_UNLOCK(mutex) atomic_flag_clear(&mutex)
#elif __GNUC__
    #define SPINLOCK_DECLARE(mutex) volatile int mutex = 0
    #define SPINLOCK_LOCK(mutex) do {} while (__sync_lock_test_and_set(&mutex, 1))
    #define SPINLOCK_UNLOCK(mutex) __sync_lock_release(&mutex)
#else
    #define SPINLOCK_DECLARE(mutex) volatile int mutex = 0
    #define SPINLOCK_LOCK(mutex) do { while (mutex == 1) {} mutex = 1; } while (0)
    #define SPINLOCK_UNLOCK(mutex) mutex = 0
#endif

typedef struct { uint64_t state, inc; } random_t;
extern void srandom_r(random_t *, uint64_t, uint64_t);
extern uint64_t random_r(random_t *);

void _fallback_entropy_getbytes(void *dest, uint32_t size) {
    static SPINLOCK_DECLARE(mutex);
    SPINLOCK_LOCK(mutex);

    static int init = 0;
    static random_t rng;

    if (!init) {
        int dummy;
        srandom_r(&rng, time(0) ^ (uint64_t) &_fallback_entropy_getbytes, (uint64_t) &dummy);
        init = 1;
    }

    char *cdest = (char *) dest;
    for (uint32_t i = 0; i < size; ++i)
        cdest[i] = (char) random_r(&rng);

    SPINLOCK_UNLOCK(mutex);
}

#if HAVE_DEV_RANDOM
    void entropy_getbytes(void *dest, uint32_t size) {
        int fd = open("/dev/urandom", O_RDONLY);
        if (fd < 0) _fallback_entropy_getbytes(dest, size);

        ssize_t sz = read(fd, dest, size);
        if (sz != size) _fallback_entropy_getbytes(dest, size);
        close(fd);
    }
#else
    void entropy_getbytes(void *dest, uint32_t size) {
        _fallback_entropy_getbytes(dest, size);
    }
#endif

#endif