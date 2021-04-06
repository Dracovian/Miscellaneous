#include <base32.h>

int BITS_PAD = 31;
char *CHARSET = "ABCDEFGHIJKLMNOPQRSTVUWXYZ234567";

void b32_encode(base32 *base) {
    size_t length = len(base->input);
    int remainder = 0, size = 0;

    for (int i = 0; i < length; i++) {
        int chr = ord(base->input[i]);

        remainder <<= 8;
        remainder |= chr;

        size += 8;
        while (size > 4) {
            size -= 5;

            int od = remainder & (BITS_PAD << size);
            od >>= size;

            char internal[2] = { chr(CHARSET, od), '\0' };
            cat(internal, base->output);
        }
    }

    if (size > 0) {
        remainder <<= (5 - size);
        int od = remainder & BITS_PAD;

        char internal[2] = { chr(CHARSET, od), '\0' };
        cat(internal, base->output);
    }

    size_t templen = 8 - (len(base->output) % 8 == 0 ? 8 : len(base->output) % 8);
    for (int i = 0; i < templen; i++) {
        char internal[2] = { '=', '\0' };
        cat(internal, base->output);
    }
}

void b32_decode(base32 *base) {
    size_t length = strlen(base->input);
    int buffer = 0, buffer_size = 0, od;

    for (int i = 0; i < length; i++) {
        char c = base->input[i];

        if ((od = charpos(CHARSET, c)) != -1) {
            buffer <<= 5;
            buffer |= od;

            buffer_size += 5;
            if (buffer_size > 7) {
                buffer_size -= 8;
                od = (buffer & (0xFF << buffer_size)) >> buffer_size;

                char internal[2] = { (char) od, '\0' };
                cat(internal, base->output);
            }
        }
    }
}