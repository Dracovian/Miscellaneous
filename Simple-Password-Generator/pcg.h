#ifndef __PASSGEN_PCG_H
#define __PASSGEN_PCG_H

#include <malloc.h>
#include <pthread.h>
#include <time.h>

#define MULTIPLIER 0x5851F42D4C957F2DULL

typedef unsigned long long qword;
typedef unsigned long      dword;

typedef struct {
    qword state,
          increment;
} pcg_t;

void pcg_step(pcg_t *pcg) {
    pcg->state *= MULTIPLIER;
    pcg->state += pcg->increment;
}

qword pcg_rotate(qword value, qword rotation) {
    return (value >> rotation) | (value << ((- rotation) & 63u));
}

qword pcg_output(qword state) {
    return pcg_rotate((state >> 32u) ^ state, state >> 59u);
}

void pcg_srandom(pcg_t *pcg, qword init, qword seq) {
    pcg->state = 0u;
    pcg->increment = (seq << 1u) | 1u;
    pcg_step(pcg);

    pcg->state += init;
    pcg_step(pcg);
}

qword pcg_random(pcg_t *pcg) {
    pcg_step(pcg);
    return pcg_output(pcg->state);
}

qword pcg_bounded(pcg_t *pcg, qword max, qword mod) {
    qword threshold = -max % max;

    while (1) {
        qword randm = pcg_random(pcg);
        if (randm >= threshold)
            return (randm % max) + mod;
    }
}

void pcg_entropy(pthread_mutex_t *mutex, void *dest, dword size) {
    pthread_mutex_lock(mutex);

    qword seed = time(NULL);
    pcg_t p;

    dword temp;
    pcg_srandom(&p, seed ^ (qword) &pcg_entropy, (qword) &temp);

    char *pdest = (char *) dest;
    for (dword i = 0u; i < size; ++i)
        pdest[i] = (char) pcg_random(&p);

    pthread_mutex_unlock(mutex);
}

#ifdef __cplusplus
};
#endif

#endif