#ifndef __LINKCRYPT_RANDOM_H
#define __LINKCRYPT_RANDOM_H

#include <stdint.h>
#include "spinlock.h"
#include "config.h"

void step_r(random_t *rng) {
    extern uint64_t multiplier;

    rng->state *= (multiplier > 0) ? multiplier : 0x5851F42D4C957F2D;
    rng->state += rng->inc;
}

void srandom_r(random_t *rng, uint64_t state, uint64_t init) {
    rng->state = 0;
    rng->inc = (init << 1) | 1;
    step_r(rng);

    rng->state += state;
    step_r(rng);
}

uint64_t output_r(uint64_t state) {
    extern uint64_t incrementer;

    uint64_t word = ((state >> ((state >> 59) + 5)) ^ state);
    word += incrementer;

    return (word >> 43) ^ word;
}

uint64_t random_r(random_t *rng) {
    uint64_t oldstate = rng->state;
    step_r(rng);

    return output_r(oldstate);
}

uint64_t incrementer;
uint64_t multiplier;

void _initialize_multiplier_and_incrementer(void) {
    extern uint64_t incrementer;
    extern uint64_t multiplier;

    random_t rng;
    uint64_t seeds[2];

    entropy_getbytes((void *) seeds, sizeof(seeds));
    srandom_r(&rng, seeds[0], seeds[1]);
    
    incrementer = random_r(&rng);
    while (multiplier == 0)
        multiplier = random_r(&rng);
}

#endif