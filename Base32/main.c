#include <stdio.h>
#include <base32.h>

int main() {
    base32 base1, base2;
    base1.input = "Hello, world!";

    b32_encode(&base1);
    fprintf(stdout, "Input: %s\nOutput: %s\n\n", base1.input, base1.output);

    base2.input = base1.output;
    b32_decode(&base2);

    fprintf(stdout, "Input: %s\nOutput: %s\n\n", base2.input, base2.output);
    return 0;
}