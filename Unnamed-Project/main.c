#include <stdio.h>
#include "irc_base/irc_command.h"

void powi64(cmd_args) {
    ul_t res = 1ull;

    for (ul_t i = 0ull; i < (ul_t) args[1]; i++)
        res *= (ul_t) args[0];

    args[2] = res;
}in

int main(void) {
    Command c_pow = command(cmd_cast powi64, P_GUEST);
    void *args[3] = { (ul_t *) 2, (ul_t *) 10, NULL };

    run(&c_pow, 3, args);
    fprintf(stdout, "%llu ^ %llu = %llu\n", (ul_t) args[0], (ul_t) args[1], (ul_t) args[2]);
    return 0;
}