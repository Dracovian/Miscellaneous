#pragma once
#include "pcg/pcg_random.hpp"
#include <sstream>
#include <string>
#include <random>

#define RNG pcg64

/*
 * SHA-1   is 160 bits and requires an 80 bit key for HMAC (64 + 16)
 * SHA-256 is 256 bits and requires a 128 bit key for HMAC (64 + 64)
 * SHA-512 is 512 bits and requires a 256 bit key for HMAC (128 + 128)
 */

struct   sha1 {      uint64_t upper;      uint16_t lower; };
struct sha256 {      uint64_t upper;      uint64_t lower; };
struct sha512 { struct sha256 upper; struct sha256 lower; };

std::string gen_sha1_key() {
    struct sha1 sha;
    RNG rng;

    rng.seed(pcg_extras::seed_seq_from<std::random_device>());
    sha.lower = rng() & 0xFF;
    sha.upper = rng();

    std::stringstream ss;
    ss << std::hex << sha.upper;
    ss << std::hex << sha.lower;

    return ss.str();
}

std::string gen_sha256_key() {
    struct sha256 sha;
    RNG rng;

    rng.seed(pcg_extras::seed_seq_from<std::random_device>());
    sha.lower = rng();
    sha.upper = rng();

    std::stringstream ss;
    ss << std::hex << sha.upper;
    ss << std::hex << sha.lower;

    return ss.str();
}

std::string gen_sha512_key() {
    struct sha512 sha;
    RNG rng;

    rng.seed(pcg_extras::seed_seq_from<std::random_device>());
    sha.lower.lower = rng();
    sha.lower.upper = rng();
    sha.upper.lower = rng();
    sha.upper.upper = rng();

    std::stringstream ss;
    ss << std::hex << sha.upper.upper;
    ss << std::hex << sha.upper.lower;
    ss << std::hex << sha.lower.upper;
    ss << std::hex << sha.lower.lower;

    return ss.str();
}
