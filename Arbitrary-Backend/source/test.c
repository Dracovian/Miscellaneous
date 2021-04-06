#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "types.h"
#include <gmp.h>

const char *longtostr(uint64_t value) {
    char tmpdata[255];
    sprintf(tmpdata, "%lu", value);

    char *data = malloc(sizeof(char) * strlen(tmpdata));
    sprintf(data, "%s", tmpdata);

    return data;
}

const char *str_uint512(uint512_t value, unsigned length) {
    mpz_t out;
    mpz_init(out);

    for (unsigned i = 0; i < length; ++i) {
        unsigned shift = 64 * (length - i - 1);

        mpz_t a, b;
        mpz_init(a);
        mpz_init(b);

        uint64_t c = value[i];
        const char *cc = longtostr(c);
        mpz_set_str(a, cc, 10);

        mpz_mul_2exp(b, a, shift);
        mpz_add(out, out, b);

        mpz_clear(a);
        mpz_clear(b);
    }

    return mpz_get_str(0, 10, out);
}

const char *str_uint256(uint256_t value, unsigned length) {
    mpz_t out;
    mpz_init(out);

    for (unsigned i = 0; i < length; ++i) {
        unsigned shift = 64 * (length - i - 1);

        mpz_t a, b;
        mpz_init(a);
        mpz_init(b);

        uint64_t c = value[i];
        const char *cc = longtostr(c);
        mpz_set_str(a, cc, 10);

        mpz_mul_2exp(b, a, shift);
        mpz_add(out, out, b);

        mpz_clear(a);
        mpz_clear(b);
    }

    return mpz_get_str(0, 10, out);
}

const char *str_uint128(uint128_t value) {
    mpz_t out;
    mpz_init(out);

    mpz_t a, b;
    mpz_init(a);
    mpz_init(b);

    uint64_t hi = (value >> 64);
    const char *c = longtostr(hi);
    mpz_set_str(a, c, 10);

    uint64_t lo = (value & UINT64_MAX);
    const char *d = longtostr(lo);
    mpz_set_str(b, d, 10);

    mpz_mul_2exp(a, a, 64);
    mpz_add(out, out, a);
    mpz_add(out, out, b);

    mpz_clear(a);
    mpz_clear(b);

    return mpz_get_str(0, 10, out);
}

int main(void) {
    uint128_t a = INT128_CONSTANT(UINT64_MAX, UINT64_MAX);

    uint256_t b = { UINT64_MAX, UINT64_MAX, UINT64_MAX, UINT64_MAX };

    uint512_t c = { UINT64_MAX, UINT64_MAX, UINT64_MAX, UINT64_MAX,
                    UINT64_MAX, UINT64_MAX, UINT64_MAX, UINT64_MAX };

    const char *uint128 = str_uint128(a);
    const char *uint256 = str_uint256(b, 4);
    const char *uint512 = str_uint512(c, 8);

    fprintf(stdout, "UINT128_MAX = %s\n", uint128);
    fprintf(stdout, "UINT256_MAX = %s\n", uint256);
    fprintf(stdout, "UINT512_MAX = %s\n", uint512);

    return 0;
}