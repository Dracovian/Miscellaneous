#include <stdio.h>
#include <string.h>
#include "include/xsocket.h"

int main(void) {
    char *data = request("https://discordapp.com/api/v6/", "GET", "Host: discordapp.com", 32768);
    char *tokens = strtok(data, "\r\n");
    char *results[255]; unsigned i = 0;

    while (tokens != NULL) {
        tokens = strtok(NULL, "\r\n");
        results[i] = tokens;
        i++;
    }

    char *jsondata = results[i - 2];
    FILE *fp = fopen("data.json", "w");

    fwrite(jsondata, strlen(jsondata), 1, fp);
    fclose(fp);

    return 0;
}
