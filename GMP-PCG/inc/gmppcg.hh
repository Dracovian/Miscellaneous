#pragma once
#include <gmp.h>

template <typename...vargs>
void mpz_init_v(vargs... args) {
    __mpz_struct *mpz_args[] = {(args)...};
    for (__mpz_struct *arg : mpz_args)
        mpz_init(arg);
}

template <typename...vargs>
void mpz_clear_v(vargs... args) {
    __mpz_struct *mpz_args[] = {(args)...};
    for (__mpz_struct *arg : mpz_args)
        mpz_clear(arg);
}

class Test {
public:
    Test(unsigned long bitsize) {
        mpz_init_v(this->state, this->increment, this->multiplier);

        mpz_set_ui(this->state, 0);               /* Initialize our RNG state with a value of 0 */
        mpz_set_ui(this->increment, 0);           /* Initialize our RNG incrementer with a value of 0 */
        mpz_set_ui(this->multiplier, 0xDEADBEEF); /* Initialize our multiplier with a hex value */
        this->bitsize = bitsize;                  /* Initialize our bit size which determines the size of the output */
    }

    ~Test() {
        mpz_clear_v(this->state, this->increment, this->multiplier);
    }

    void lshift(mpz_t output, mpz_t value, mpz_t bits) {
        mp_bitcnt_t bit = mpz_get_ui(bits);
        mpz_mul_2exp(output, value, bit);
    }

    void rshift(mpz_t output, mpz_t value, mpz_t bits) {
        mp_bitcnt_t bit = mpz_get_ui(bits);
        mpz_div_2exp(output, value, bit);
    }

    void step() {
        mpz_mul(this->state, this->state, this->multiplier);
        mpz_add(this->state, this->state, this->increment);
    }

    void rotate(mpz_t output, mpz_t value, mpz_t rotation) {
        mpz_t lside, rside, roinv, robits;
        mpz_init_v(lside, rside, roinv, robits);
        mpz_set_ui(robits, this->bitsize - 1);

        mp_bitcnt_t rotbits = mpz_get_ui(rotation);
        mpz_set_ui(roinv, ~rotbits);
        
        mpz_t lside_a, rside_a;
        mpz_init_v(lside_a, rside_a);

        mpz_div_2exp(lside, value, rotbits);
        mpz_and(rside_a, roinv, robits);

        this->lshift(rside, value, rside_a);
        mpz_ior(output, lside, rside);

        mpz_clear_v(lside, rside, roinv, robits, lside_a, rside_a);
    }

    void output(mpz_t output, mpz_t state) {
        mpz_t param1, param2, param1_a;
        mpz_init_v(param1, param2, param1_a);

        mpz_div_2exp(param1_a, state, this->bitsize / 2);
        mpz_xor(param1, param1_a, state);

        mpz_div_2exp(param2, state, this->bitsize - 5);
        this->rotate(output, param1, param2);

        mpz_clear_v(param1, param2, param1_a);
    }

    void srandom(mpz_t initial, mpz_t sequence) {
        mpz_t inc_lside, inc_rside;
        mpz_init_v(inc_lside, inc_rside);
        mpz_set_ui(inc_rside, 1);

        mpz_mul_2exp(inc_lside, sequence, 1);
        mpz_ior(this->increment, inc_lside, inc_rside);
        this->step();

        mpz_add(this->state, this->state, initial);
        this->step();

        mpz_clear_v(inc_lside, inc_rside);
    }

    void random(mpz_t output) {
        this->step();
        this->output(output, this->state);
    }

    void boundedrand(mpz_t output, mpz_t maximum) {
        this->random(output);
        mpz_add_ui(maximum, maximum, 1);
        mpz_mod(output, output, maximum);
    }

    void entropy(unsigned long seed) {
        mpz_t sr_param1, sr_param2;
        mpz_init_v(sr_param1, sr_param2);
        unsigned long temporary;
        
        mpz_set_ui(sr_param1, seed ^ (unsigned long) this);
        mpz_set_ui(sr_param2, (unsigned long) &temporary);

        this->srandom(sr_param1, sr_param2);
        mpz_t seeds[2];

        for (int i = 0; i < 2; ++i)
            this->random(seeds[i]);

        this->srandom(seeds[0], seeds[1]);
        mpz_clear_v(sr_param1, sr_param2);
    }

private:
    mpz_t state;
    mpz_t increment;
    mpz_t multiplier;

    mp_bitcnt_t bitsize;
};
