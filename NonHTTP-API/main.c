#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "inc/cfg/json.h"

char *readfile(const char *filename) {
    FILE *fp = fopen(filename, "r");
    fseek(fp, 0, SEEK_END);

    long filesize = ftell(fp);
    fseek(fp, 0, SEEK_SET);

    char *buffer = malloc(sizeof(char *) * filesize);
    fread(buffer, sizeof(char), filesize, fp);
    fclose(fp);

    return buffer;
}

int jsoneq(const char *code, jsontoken_t *token, const char *s) {
    if (token->type == STRING) {
        if (strlen(s) == token->end - token->start && strncmp(code + token->start, s, token->end - token->start) == 0)
            return 0;
    }

    return -1;
}

int main(int argc, char **argv) {
    if (argc != 3) {
        fprintf(stdout, "%s {filename} {key}\n", argv[0]);
        return -1;
    } else {
        char *jsondata = readfile(argv[1]);

        json_parser parser;
        jsontoken_t tokens[128];

        json_init(&parser);
        int r = json_parse(&parser, jsondata, (int) strlen(jsondata), tokens, 128);

        if (r < 0) {
            fprintf(stderr, "[%d] Error occured when parsing JSON data.\n", r);
            return -1;
        }

        for (int i = 0; i < 128; i++) {
            if (jsoneq(jsondata, &tokens[i], argv[2]) == 0) {
                fprintf(stdout, "%.*s\n", tokens[i + 1].end - tokens[i + 1].start, jsondata + tokens[i + 1].start);
            }
        }

        free(jsondata);
    }

    return 0;
}
