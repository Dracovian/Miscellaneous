#ifndef __XSOCKET_H
#define __XSOCKET_H

#include <stdbool.h>

#ifdef PLATFORM_WINDOWS

#include <winsock2.h>
#include <Windows.h>

typedef SOCKET socket_t;
typedef WSADATA winwsa_t;

#else

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

typedef int socket_t;
typedef void *winwsa_t;

#endif /* PLATFORM_WINDOWS */

#define TCP SOCK_STREAM
#define UDP SOCK_DGRAM
typedef unsigned short int port;

/* XSocket Functions */

bool check_port_is_valid(port);
bool check_wsa_status(int, int, winwsa_t *);

bool check_port_is_open_ipv4(const char *, port, int);
bool check_port_is_open_ipv6(const char *, port, int);

#endif /* __XSOCKET_H */
