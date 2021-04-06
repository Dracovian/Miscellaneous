#include <stdio.h>
#include <string.h>
#include "base32.h"

const char BASE32_CHARSET[33] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ234567";

int get_length(int length) {
	return (length % 5 == 0)
		? 8 * (length / 5)
		: 8 * ((length / 5) + 1);
}

void pad_input(char *input, int length) {
	for (int i = 0; i < length; ++i)
		input[i] = '=';
}

int get_octet(int block) {
	return (block * 5) / 8;
}

int get_offset(int block) {
	return (3 - (5 * block) % 8);
}

char shift_right(char c, int offset) {
	return offset > 0 ? c >> offset : c << -offset;
}

char shift_left(char c, int offset) {
	return shift_right(c, -offset);
}

char encode_char(char c) {
	return BASE32_CHARSET[c & 0x1F];
}

int decode_char(char c) {
	int retval = -1;

	if (c >= 'A' && c <= 'Z')
		retval = c - 'A';

	else if (c >= '2' && c <= '7')
		retval = c - '2' + 26;

	return retval;
}

void encode_sequence(const char *input, int length, char *encoded) {
	for (int block = 0; block < 8; block++) {
		int octet = get_octet(block),
		    junk  = get_offset(block);

		if (octet >= length) {
			pad_input(&encoded[block], 8 - block);
			return;
		}

		char c = shift_right(input[octet], junk);
		if (junk < 0 && octet < length - 1)
			c |= shift_right(input[octet + 1], 8 + junk);

		encoded[block] = encode_char(c);
	}
}

int decode_sequence(const char *input, char *decoded) {
	decoded[0] = 0;

	for (int block = 0; block < 8; block++) {
		int offset = get_offset(block),
		    octet  = get_octet(block);

		int c = decode_char(input[block]);
		if (c < 0) return octet;

		decoded[octet] |= shift_left((char) c, offset);
		if (offset < 0)
			decoded[octet + 1] = shift_left((char) c, 8 + offset);
	}

	return 5;
}

void b32_encode(const char *input, int length, char *output) {
	for (int i = 0, j = 0; i < length; i += 5, j += 8)
		encode_sequence(&input[i], MIN(length - i, 5), &output[j]);
}

int b32_decode(const char *input, char *output) {
	int written = 0;

	for (int i = 0, j = 0;; i += 8, j += 5) {
		int n = decode_sequence(&input[i], &output[j]);
		written += n;

		if (n < 5) return written;
	}
}
