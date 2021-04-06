#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include "../include/xsocket.h"

/******************************************************************/
/*               Non-library functions for XSocket                */
/******************************************************************/

bool check_wsa_status(int major, int minor, winwsa_t *wsa) {
#ifdef PLATFORM_WINDOWS
    return (WSAStartup(MAKEWORD(major, minor), wsa) != 0);
#endif

    return true;
}

/******************************************************************/
/*              Custom library functions for XSocket              */
/******************************************************************/

socket_t open_socket(int domain, int type, int proto) {
    winwsa_t wsa;
    socket_t s = socket(domain, type, proto);

#ifdef PLATFORM_WINDOWS
    if (s == INVALID_SOCKET) {
        socket_error("Unable to create a socket.\n");
        return -1;
    }
#else
    if (s < 0) {
        socket_error("Unable to create a socket.\n");
        return -1;
    }
#endif
    if (!check_wsa_status(2, 2, &wsa)) {
        socket_error("WSA didn't initialize correctly.\n");
        return -1;
    }

    return s;
}

void close_socket(socket_t s) {
#ifdef PLATFORM_WINDOWS
    closesocket(s);
    WSACleanup();
#else
    shutdown(s, 2);
#endif
}

bool socket_error(const char *message, ...) {
    va_list vlist;
    va_start(vlist, message);

#ifdef MODE_DEBUG
    vfprintf(stderr, message, vlist);
#endif
    va_end(vlist);

    return false;
}

char *parse_domain(const char *domain) {
    struct addrinfo *hostname, *result;
    int error = getaddrinfo(domain, NULL, NULL, &hostname);

    if (error != 0) {
        fprintf(stderr, "Error in getaddrinfo: %s\n", gai_strerror(error));
        return NULL;
    }

    for (result = hostname; result != NULL; result = result->ai_next) {
        char *host = malloc(sizeof(char) * 1025);
        getnameinfo(result->ai_addr, result->ai_addrlen, host, 1025, NULL, 0, 0);

        if (*host != '\0')
            return host;

        free(host);
        freeaddrinfo(hostname);
    }

    freeaddrinfo(result);
    return NULL;
}

char *request(const char *url, char *method, char *headers, unsigned long length) {
    char bf[strlen(url)];
    strcpy(bf, url);

    unsigned len = 0; char *data[256];
    char *d = strtok(bf, "/");

    while (d != NULL) {
        data[len] = d;
        len++;

        d = strtok(NULL, "/");
    }

    char *scheme = data[0];
    char *domain = data[1];

    char uri[1024] = "";
    strcat(uri, method);
    strcat(uri, " ");

    for (unsigned i = 2; i < len; i++) {
        strcat(uri, "/");
        strcat(uri, data[i]);
    }

    strcat(uri, " HTTP/1.1\r\n");
    strcat(uri, headers);
    strcat(uri, "\r\n\r\n");

    bool https = strcmp(scheme, "https:") == 0 ? true : false;
    char *buffer = malloc(sizeof(char) * length);

    socket_t socket = open_socket(AF_INET, TCP, 0);
    char *address = parse_domain(domain);

    struct sockaddr_in s;
    s.sin_addr.s_addr = inet_addr(address);
    s.sin_family = AF_INET;
    s.sin_port = htons((https) ? 443 : 80);

    if (connect(socket, (struct sockaddr *) &s, sizeof(s)) < 0) {
        fprintf(stderr, "Unable to connect to %s.\n", domain);
        return NULL;
    }

    if (https) {
        SSL_library_init();

        SSL_CTX *ctx = SSL_CTX_new(SSLv23_client_method());
        SSL *conn = SSL_new(ctx);

        SSL_set_fd(conn, socket);
        SSL_connect(conn);

        SSL_write(conn, uri, (int) strlen(uri));
        SSL_read(conn, buffer, (int) length);

        SSL_free(conn);
    } else {
        write(socket, uri, strlen(uri));
        read(socket, buffer, length);
    }

    close_socket(socket);
    return buffer;
}
