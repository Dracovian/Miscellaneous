#ifndef __API_JSON_H
#define __API_JSON_H

#include "../global.h"

enum jsontype {
    UNDEFINED = 0,
    OBJECT,
    ARRAY,
    STRING,
    PRIMITIVE
};

enum jsonerr {
    ERROR_PART = -3,
    ERROR_INVAL,
    ERROR_NOMEM
};

typedef struct {
    enum jsontype type;    /* The data type for the value of the parsed token. */
    int start,             /* The starting position of the token.              */
        end,               /* The ending position of the token.                */
        size;              /* The number of nested tokens.                     */

#ifdef JSON_PARENT_LINKS
    int parent;
#endif
} jsontoken_t;

typedef struct {
    int position, /* Offset in the JSON string. */
        next,     /* Next token to allocate.    */
        super;    /* Parent object/array node.  */
} json_parser;

INIT_EXTERN_C()
    API_FUNC void json_init(json_parser *);
    API_FUNC int json_parse(json_parser *, const char *, int, jsontoken_t *, int);

    API_FUNC jsontoken_t *json_allocate_token(json_parser *, jsontoken_t *, int);
    API_FUNC void json_fill_token(jsontoken_t *, enum jsontype, int, int);

    API_FUNC int json_parse_primitive(json_parser *, const char *, int, jsontoken_t *, int);
    API_FUNC int json_parse_string(json_parser *, const char *, int, jsontoken_t *, int);
EXIT_EXTERN_C()

#endif