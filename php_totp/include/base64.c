#include "base64.h"
const char BASE64_CHARSET[65] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

int b64_length(int length) {
	int ret = length;
	if (length % 3 != 0)
		ret += 3 - (length % 3);

	ret /= 3;
	ret *= 4;
	return ret;
}

void b64_encode(const byte *input, int length, char *output) {
	int elen = b64_length(length), v;

	for (int i = 0, j = 0; i < length; i += 3, j += 4) {
		v = input[i];
		v = i + 1 < length ? v << 8 | input[i + 1] : v << 8;
		v = i + 2 < length ? v << 8 | input[i + 2] : v << 8;

		output[j    ] = BASE64_CHARSET[(v >> 18) & 0x3F];
		output[j + 1] = BASE64_CHARSET[(v >> 12) & 0x3F];

		if (i + 1 < length)
			output[j + 2] = BASE64_CHARSET[(v >> 6) & 0x3F];
		else
			output[j + 2] = '=';

		if (i + 2 < length)
			output[j + 3] = BASE64_CHARSET[v & 0x3F];
		else
			output[j + 3] = '=';
	}
}
