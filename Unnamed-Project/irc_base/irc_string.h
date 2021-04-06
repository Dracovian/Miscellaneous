#ifndef __IRC_STRING_H
#define __IRC_STRING_H

#include "irc_base.h"
#include <string.h>
#include <malloc.h>

typedef struct {
    char *data;
    ul_t length;
} String;

String string(char *data, ul_t length) { return (String) { data, length }; }
String ez_string(char *data) { return (String) { data, strlen(data) }; }

String concat(String *str1, String *str2) {
    ul_t str3_len = str1->length + str2->length;
    char *str3_data = malloc(sizeof(char) * str3_len);

    strcat(str3_data, str1->data);
    strcat(str3_data, str2->data);
    return string(str3_data, str3_len);
}

bool contains(String *string, String *search) {
    return strstr(string->data, search->data) != NULL;
}

#endif