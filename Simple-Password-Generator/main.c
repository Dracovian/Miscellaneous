#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pcg.h"

#define UPPER   "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
#define LOWER   "abcdefghijklmnopqrstuvwxyz"
#define NUMBER  "0123456789"
#define SYMBOLS "`~!@#$%^&*()_-+={}[]\\|:;\"'<>,.?/"

char chrtoupper(const char input) {
    if (input >= 'a' && input <= 'z')
        return input - ' ';
}

void strtoupper(char *input) {
    for (unsigned i = 0U; i < strlen(input); i++)
        input[i] = chrtoupper(input[i]);
}

char *get_charset_group(const char groupid) {
    switch (groupid) {
        case 'U':
            return UPPER;
        case 'L':
            return LOWER;
        case 'N':
            return NUMBER;
        case 'S':
            return SYMBOLS;
        default:
            break;
    }

    fprintf(stderr, "Invalid group '%c'.\n", groupid);
    exit(-1);
}

void generate_password(char charset[98], unsigned length) {
    pthread_mutex_t mutex;
    if (pthread_mutex_init(&mutex, NULL) != 0) {
        fprintf(stderr, "Unable to initialize mutual exclusions!\n");
        exit(-1);
    }

    qword seeds[2];
    pcg_entropy(&mutex, (void *) seeds, sizeof(seeds));

    pcg_t pcg;
    pcg_srandom(&pcg, seeds[0], seeds[1]);

    char *output = malloc(sizeof(char) * (length + 1U));
    for (unsigned i = 0; i < length; ++i) {
        qword rval = pcg_bounded(&pcg, strlen(charset), 0ULL);
        output[i] = charset[rval];
    }

    output[length + 1] = '\0';
    fprintf(stdout, "%s\n", output);
    free(output);
}

void print_help() {
    char *usage = "Usage:\n"
                  "\t--charset <GROUP>\n"
                  "\t--length <NUMBER>\n\n"
                  "Groups:\n"
                  "\tU - Uppercase English Alphabet\n"
                  "\tL - Lowercase English Alphabet\n"
                  "\tN - Numbers 0 to 9\n"
                  "\tS - Special English Characters\n\n"
                  "Example:\n"
                  "\t--charset ULNS --length 30\n"
                  "\t--charset LN --length 12\n"
                  "\t--charset LUN --length 16";

    fprintf(stdout, "%s\n", usage);
}

int main(int argc, char *argv[]) {
    if (argc != 5) {
        print_help();
        return 1;
    }
    
    char *charset = argv[2];
    unsigned length;

    if (strcmp(argv[1], "--charset") != 0 || strcmp(argv[3], "--length") != 0) {
        print_help();
        return 1;
    }

    strtoupper(charset);
    length = strtoul(argv[4], 0, 10);

    char charset_characters[98];
    for (unsigned i = 0U; i < strlen(charset); i++)
        strcat(charset_characters, get_charset_group(charset[i]));

    generate_password(charset_characters, length);
    return 0;
}
