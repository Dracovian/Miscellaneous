#ifndef __IRC_COMMAND_H
#define __IRC_COMMAND_H

#include "irc_base.h"
#include "enum_perms.h"

#define cmd_cast (void (*)(int, void*[]))
#define cmd_args int argc, void *args[]

typedef struct {
    void (*fun)(int, void*[]); // The function pointer.
    enum Permissions perms;      // The command permissions.
} Command;

Command command(void (*f)(int argc, void *args[]), enum Permissions perms) {
    return (Command) { f, perms };
}

void run(Command *com, int argc, void *args[]) {
    com->fun(argc, args);
}

#endif