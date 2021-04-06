#ifndef __PCG_H
#define __PCG_H

#include "global.h"
#define PCG64_MULTIPLIER 6364136223846793005ULL

typedef struct Random {

	i64 state,     // The current value of the PRNG.
	    increment; // The value that we'll add to the PRNG state on each subsequent tick.
} random_t;


void pcg_step(random_t *);
void pcg_srandom(random_t *, i64, i64);

i64 pcg_rotate(i64, i64);
i64 pcg_output(i64);

i64 pcg_random(random_t *);
i64 pcg_bounded(random_t *, i64, i64);

#endif // __PCG_H
