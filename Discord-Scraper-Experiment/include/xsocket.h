/*
 * xsocket.h
 *
 * Dracovian <https://github.com/Dracovian>
 * May 8, 2020
 *
 * Make a cross-platform network sockets library.
 */

#ifndef __INC_XSOCKET_H
#define __INC_XSOCKET_H

#include "compiler.h"    /* We need to know which platform we're using */
#include "mytypes.h"     /* Include our own custom data types for this */

#include <stdarg.h>      /* Include the standard arguments library     */
#include <openssl/ssl.h> /* Include the OpenSSL library for HTTPS      */

#ifdef PLATFORM_WINDOWS

#include <winsock2.h>
#include <ws2tcpip.h>
#include <windows.h>

typedef SOCKET socket_t; /* Winsock has its own data type for sockets. */
typedef WSADATA winwsa_t; /* Winsock requires WSA checking for some reason. */

#else /* We're not running on Windows */

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netdb.h>

typedef int socket_t; /* Winsock has its own data type for sockets, so we have to do this shit. */
typedef void *winwsa_t; /* Winsock requires WSA checking for some reason, so we have to do this as well. */

#endif /* Sockets library */

/* Socket type shorthand */
#define TCP SOCK_STREAM
#define UDP SOCK_DGRAM

socket_t open_socket(int, int, int);
void close_socket(socket_t);

bool socket_error(const char *, ...);
char *parse_domain(const char *);

char *request(const char *, char *, char *, unsigned long);

#endif /* __INC_XSOCKET_H */
