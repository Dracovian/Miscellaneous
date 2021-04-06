#ifndef __ENUM_PERMS_H
#define __ENUM_PERMS_H

enum Permissions {
    P_BANNED = 0x00,
    P_GUEST, P_MEMBER,
    P_VIP1 = 0x04,
    P_VIP2 = 0x08,
    P_VIP3 = 0x10,
    P_VIP4 = 0x20,
    P_VIP5 = 0x40,
    P_VIP6 = 0x80
};

/*
 * (P_VIP1 + P_VIP2) & P_VIP2 == P_VIP2
 * (P_VIP1 + P_VIP2) & P_VIP1 == P_VIP1
 * (P_VIP1 + P_VIP2) & P_VIP3 == 0 (no permissions)
 */

#endif