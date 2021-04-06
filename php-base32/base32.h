#include <stdlib.h>
#include <string.h>

#define BASE32_CHARSET "ABCDEFGHIJKLMNOPQRSTUVWXYZ234567"
#define min(x, y) ((x) < (y) ? (x) : (y))

/*
 * Generic functions.
 */

void pad(char *buffer, int length) {
    for (int i = 0; i < length; i++)
        buffer[i] = '=';
}

size_t getlen(size_t length) {
    return (length % 5 == 0    )
        ? 8 * (length / 5      )
        : 8 * ((length / 5) + 1);
}

/*
 * Encode/decode character functions.
 */

char encode_char(char c) {
    return BASE32_CHARSET[c & 0x1F];
}

int decode_char(char c) {
    int retval = -1;

    if (c >= 'A' && c <= 'Z')
        retval = c - 'A';

    if (c >= '2' && c <= '7')
        retval = c - '2' + 26;

    return retval;
}

/*
 * Gather octet and offset functions.
 */

int get_octet(int block) {
    return (block * 5) / 8;
}

int get_offset(int block) {
    return (3 - (5 * block) % 8);
}

/*
 * Character shift functions.
 */

char shift_right(char byte, int offset) {
    return offset > 0 ? byte >> offset : byte << -offset;
}

char shift_left(char byte, int offset) {
    return shift_right(byte, -offset);
}

/*
 * Encode/decode sequence functions.
 */

void encode_sequence(const char *input, size_t length, char *coded) {
    for (int block = 0; block < 8; block++) {
        int octet = get_octet(block),
            junk  = get_offset(block);

        if (octet >= length) {
            pad(&coded[block], 8 - block);
            return;
        }

        char c = shift_right(input[octet], junk);
        if (junk < 0 && octet < length - 1)
            c |= shift_right(input[octet + 1], 8 + junk);

        coded[block] = encode_char(c);
    }
}

int decode_sequence(const char *input, char *plain) {
    plain[0] = 0;

    for (int block = 0; block < 8; block++) {
        int offset = get_offset(block),
            octet  = get_octet(block);

        int c = decode_char(input[block]);
        if (c < 0) return octet;

        plain[octet] |= shift_left((char) c, offset);
        if (offset < 0)
            plain[octet + 1] = shift_left((char) c, 8 + offset);
    }

    return 5;
}

/*
 * Base32 encode/decode functions.
 */

void encode(char *plain, size_t length, char *coded) {
    for (size_t i = 0, j = 0; i < length; i += 5, j += 8)
        encode_sequence(&plain[i], min(length - i, 5), &coded[j]);
}

size_t decode(char *coded, char *plain) {
    size_t written = 0;

    for (size_t i = 0, j = 0;; i += 8, j += 5) {
        int n = decode_sequence(&coded[i], &plain[j]);
        written += n;

        if (n < 5)
            return written;
    }
}
