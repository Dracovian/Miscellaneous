#ifndef __LINKCRYPT_SIMD_H
#define __LINKCRYPT_SIMD_H

#if defined(__i386__) || defined(__x86_64__)
    #define cpucheck(i,s) ((i & (1 << s)) != 0)
    #define simdcheck(c,s) (c.s) ? 1 : 0

    void __cpuid(int info[4], int level) {
        __asm__("cpuid" : "=a"(info[0]), "=b"(info[1]), "=c"(info[2]), "=d"(info[3])
                        : "a"(level), "c"(0));
    }
#endif

#endif