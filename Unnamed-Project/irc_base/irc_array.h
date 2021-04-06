#ifndef __IRC_ARRAY_H
#define __IRC_ARRAY_H

#include "irc_base.h"
#include <malloc.h>
#include <string.h>
#include <stdarg.h>

typedef struct {
    void **data;
    ul_t size;
} Array;

Array array(ul_t size, ...) {
    void **arr = malloc(sizeof(void *) * size);

    va_list vlist;
    va_start(vlist, size);

    for (ul_t i = 0; i < size; i++) {
        void *arg = va_arg(vlist, void *);
        arr[i] = arg;
    }

    va_end(vlist);
    return (Array) { arr, size };
}

void append(Array *arr, void *data) {
    ul_t size = arr->size;
    void **tmp = realloc(arr->data, sizeof(void *) * size + 1ull);

    tmp[size] = data;
    arr->data = tmp;
    arr->size++;
}

void set(Array *arr, ul_t index, void *data) {
    if (arr->size <= index) return;
    arr->data[index] = data;
}

#endif