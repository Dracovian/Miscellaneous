#include <strfunc.h>

int charpos(const char *input, char find) {
    for (int i = 0; i < strlen(input); i++)
        if (input[i] == find)
            return i;

    return -1;
}