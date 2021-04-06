#include <stdio.h>
#include <pthread.h>
#include "xsocket.h"

typedef struct {
    union {
        char *ipv4;
        char *ipv6;
    } addr;

    bool is_ipv6;
    int proto;
    port p;
} args;

void *arghandler(void *argv) {
    args *arg = (args *) argv;

    if (arg->is_ipv6) {
        if (check_port_is_open_ipv6(arg->addr.ipv6, arg->p, arg->proto))
            fprintf(stdout, "Port %s/%hu is open for %s.\n", arg->proto == TCP ? "TCP" : "UDP", arg->p, arg->addr.ipv6);
    } else {
        if (check_port_is_open_ipv4(arg->addr.ipv4, arg->p, arg->proto))
            fprintf(stdout, "Port %s/%hu is open for %s.\n", arg->proto == TCP ? "TCP" : "UDP", arg->p, arg->addr.ipv4);
    }

    return 0;
}

int main(void) {
    args arg;
    arg.is_ipv6 = false;
    arg.addr.ipv4 = "127.0.0.1";
    arg.proto = TCP;

    pthread_mutex_t mutex;
    if (pthread_mutex_init(&mutex, 0) != 0) {
        fprintf(stderr, "Mutex initialization failed!\n");
        return -1;
    }

    const int rounds = 3;
    pthread_t thread[rounds];
    port p[] = { 80, 443, 10000 };

    for (int i = 0; i < rounds; ++i) {
        arg.p = p[i];

        int t = pthread_create(&thread[i], 0, arghandler, &arg);
        if (t != 0) {
            fprintf(stderr, "Cannot create thread!\n");
            pthread_mutex_destroy(&mutex);
            return -1;
        }

        pthread_join(thread[i], 0);
    }

    pthread_mutex_destroy(&mutex);
    return 0;
}