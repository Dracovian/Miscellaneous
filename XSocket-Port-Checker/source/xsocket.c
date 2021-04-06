#include <stdio.h>
#include <stdarg.h>
#include "xsocket.h"

void close_socket(socket_t sock) {
    #ifdef PLATFORM_WINDOWS
    closesocket(sock);
    WSACleanup();
    #else
    shutdown(sock, 2);
    #endif
}

socket_t open_socket(int domain, int type, int proto) {
    socket_t sock = socket(domain, type, proto);

    #ifdef PLATFORM_WINDOWS
    if (sock == INVALID_SOCKET)
        return -1;
    #else
    if (sock < 0)
        return -1;
    #endif

    return sock;
}

bool check_wsa_status(int major, int minor, winwsa_t *wsa) {
    #ifdef PLATFORM_WINDOWS
    return (WSAStartup(MAKEWORD(major, minor), wsa) != 0);
    #endif

    return true;
}

bool check_port_is_valid(port p) {
    return (p > 0 && p < 65536);
}

bool check_port_is_open_ipv4(const char *addr, port p, int protocol) {
    winwsa_t wsa;
    socket_t sock = open_socket(AF_INET, protocol, 0);

    if (!check_port_is_valid(p)) {
        fprintf(stderr, "Invalid port number %hu.\n", p);
        return false;
    }

    if (!check_wsa_status(2, 2, &wsa)) {
        fprintf(stderr, "Unable to start WSA.\n");
        return false;
    }

    struct sockaddr_in sin;
    sin.sin_addr.s_addr = inet_addr(addr);
    sin.sin_family = AF_INET;
    sin.sin_port = htons(p);

    if (connect(sock, (struct sockaddr *) &sin, sizeof sin) < 0) {
        fprintf(stderr, "Unable to connect to %s:%hu\n", addr, p);
        return false;
    }

    close_socket(sock);
    return true;
}

bool check_port_is_open_ipv6(const char *addr, port p, int protocol) {
    winwsa_t wsa;
    socket_t sock = open_socket(AF_INET6, protocol, 0);

    if (!check_port_is_valid(p)) {
        fprintf(stderr, "Invalid port number %hu.\n", p);
        return false;
    }

    if (!check_wsa_status(2, 2, &wsa)) {
        fprintf(stderr, "Unable to start WSA.\n");
        return false;
    }

    struct sockaddr_in6 sin;
    inet_pton(AF_INET6, addr, &(sin.sin6_addr));
    sin.sin6_family = AF_INET6;
    sin.sin6_port = htons(p);

    if (connect(sock, (struct sockaddr *) &sin, sizeof sin) < 0) {
        fprintf(stderr, "Unable to connect to [%s]:%hu\n", addr, p);
        return false;
    }

    close_socket(sock);
    return true;
}