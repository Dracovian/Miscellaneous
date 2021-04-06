#ifndef _PCG_H
#define _PCG_H

#include <time.h>

// Create a shorthand definition for unsigned.
#ifndef U
#define U unsigned
#endif

// Introduce atomics to make our spinlock functions thread-safe.
#if __STDC_VERSION__ >= 201112L && !defined(__STDC_NO_ATOMICS__)
    #include <stdatomic.h>
    #define SPINLOCK_DECLARE(mutex) volatile int mutex = ATOMIC_FLAG_INIT
    #define SPINLOCK_LOCK(mutex) do {} while (atomic_flag_test_and_set(&mutex))
    #define SPINLOCK_UNLOCK(mutex) atomic_flag_clear(&mutex)
#elif __GNUC__
    #define SPINLOCK_DECLARE(mutex) volatile int mutex = 0
    #define SPINLOCK_LOCK(mutex) do {} while(__sync_lock_test_and_set(&mutex,1))
    #define SPINLOCK_UNLOCK(mutex) __sync_lock_release(&mutex)
#else
    #warning No implementation of atomics provided, no thread safety guaranteed.
    #define SPINLOCK_DECLARE(mutex) volatile int mutex = 0
    #define SPINLOCK_LOCK(mutex) do { while (mutex == 1){} mutex = 1; } while(0)
    #define SPINLOCK_UNLOCK(mutex) mutex = 0
#endif // End of spinlock definitions

// Create our random data type from a structure.
typedef struct Random {
    U long long state, // Store the current value of our PRNG.
            increment; // Store what will be added on the next step of the PRNG.
} random_t;

// Take a step in our PRNG method (apply an increment and the static multiplier)
void pcg_step(random_t *rand) {
    rand->state = rand->state * 6364136223846793005ull + rand->increment;
}

// Initialize and step our seeded PRNG method.
void pcg_srandom(random_t *rand, U long long seq, U long long inc) {
    rand->state = 0u;
    rand->increment = (seq << 1u) | 1u;
    pcg_step(rand);

    rand->state += inc;
    pcg_step(rand);
}

// Output the rotated value of an input value within a 64-bit limitation.
U long long pcg_rotate(U long long val, U long long rotation) {
    return (val >> rotation) | (val << ((-rotation) & 63u));
}

// Return a rotated output of our PRNG state.
U long long pcg_output(U long long state) {
    return pcg_rotate((state >> 32u) ^ state, state >> 59u);
}

// Return a randomly generated value from 0x0 to 0xFFFFFFFFFFFFFFFF.
U long long pcg_random(random_t *rand) {
    pcg_step(rand);
    return pcg_output(rand->state);
}

// Return a randomly generated value that fits within a given min and max value.
U long long pcg_boundedrand(random_t *rnd, U long long min, U long long max) {
    U long long threshold = -max % max;

    // Initialize a never-ending loop until we generate a value that fits.
    for (;;) {
        U long long r = pcg_random(rnd);

        if (r >= threshold)
            return (r % max) + min;
    }
}

void entropy_getbytes(void *destination, U long size) {
    static SPINLOCK_DECLARE(mutex);
    SPINLOCK_LOCK(mutex);

    static int init = 0;
    static random_t rand;

    // Prevent this from being initialized multiple times from race conditions.
    if (init == 0) {
        int tmpvar; // Just define this to obtain its point in memory.

        pcg_srandom(
                &rand,
                (U long long) &tmpvar,
                (U long long) ((U) time(NULL) ^ (uintptr_t) &entropy_getbytes)
        );

        // End this loop right here.
        init++;
    }

    char *dest = (char *) destination;
    for (U long i = 0; i < size; ++i)
        dest[i] = (char) pcg_random(&rand);

    SPINLOCK_UNLOCK(mutex);
}

// Time to undefine our shorthand unsigned modifier.
#ifdef U
#undef U
#endif

#endif // _PCG_H