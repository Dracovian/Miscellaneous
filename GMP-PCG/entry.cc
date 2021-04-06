#include "inc/gmppcg.hh"
#include <cstdio>
#include <ctime>

int main(void) {
    unsigned long bits = 8192;   /* My attempt at a potential PCG-8192 */
    Test *test = new Test(bits); /* Initialize our PRNG state and incrementer */
    test->entropy(std::time(0)); /* Seed the PRNG using the current system time */
    
    mpz_t random, maximum;
    mpz_init_v(random, maximum);
    
    mpz_set_ui(maximum, 1);               /* Set our maximum to 1 since that's what we're going to shift */
    mpz_mul_2exp(maximum, maximum, bits); /* Shift 1 << bits to get the maximum value of our bits */

    test->boundedrand(random, maximum);
    mpz_out_str(stdout, 10, random);
    std::printf("\n");

    delete test;
    mpz_clear_v(random, maximum);
    return 0;
}