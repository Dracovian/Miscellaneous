#include <stddef.h>
#include "json.h"

API_FUNC void json_init(json_parser *parser) {
    parser->position = parser->next = 0;
    parser->super = -1;
}

API_FUNC void json_fill_token(jsontoken_t *token, enum jsontype type, int start, int end) {
    token->type = type;
    token->start = start;
    token->end = end;
}

API_FUNC int json_parse_primitive(json_parser *parser, const char *code, int length, jsontoken_t *tokens, int tokenamt) {
    int start = parser->position;
    jsontoken_t *token;

    for (; parser->position < length && code[parser->position] != '\0'; parser->position++) {
        switch (code[parser->position]) {
            #ifndef JSON_STRICT
            case ':':
            #endif
            case '\t':
            case '\r':
            case '\n':
            case ' ':
            case ',':
            case ']':
            case '}':
                goto found;

            default:
                break;
        }

        if (code[parser->position] < 32 || code[parser->position] >= 127) {
            parser->position = start;
            return ERROR_INVAL;
        }
    }

    #ifdef JSON_STRICT
    parser->position = start;
    return ERROR_PART;
    #endif

found:
    if (tokens == NULL) {
        parser->position--;
        return 0;
    }

    token = json_allocate_token(parser, tokens, tokenamt);
    if (token == NULL) {
        parser->position = start;
        return ERROR_NOMEM;
    }

    json_fill_token(token, PRIMITIVE, start, parser->position);

    #ifdef JSON_PARENT_LINKS
    token->parent = parser->super;
    #endif

    parser->position--;
    return 0;
}

API_FUNC int json_parse_string(json_parser *parser, const char *code, int length, jsontoken_t *tokens, int tokenamt) {
    int start = parser->position;
    jsontoken_t *token;
    parser->position++;

    for (; parser->position < length && code[parser->position] != '\0'; parser->position++) {
        char ch = code[parser->position];

        if (ch == '\"') {
            if (tokens == NULL) return 0;
            token = json_allocate_token(parser, tokens, tokenamt);

            if (token == NULL) {
                parser->position = start;
                return ERROR_NOMEM;
            }

            json_fill_token(token, STRING, start + 1, parser->position);

            #ifdef JSON_PARENT_LINKS
            token->parent = parser->super;
            #endif

            return 0;
        }

        if (ch == '\\' && parser->position + 1 < length) {
            int i;

            parser->position++;
            switch (code[parser->position]) {
                case '\"':
                case '/':
                case '\\':
                case 'b':
                case 'f':
                case 'r':
                case 'n':
                case 't':
                    break;

                case 'u':
                    parser->position++;
                    for (i = 0; i < 4 && parser->position < length && code[parser->position] != '\0'; i++) {
                        if (!((code[parser->position] >= 48 && code[parser->position] <= 57 ) ||
                              (code[parser->position] >= 65 && code[parser->position] <= 70 ) ||
                              (code[parser->position] >= 97 && code[parser->position] <= 102)))
                        {
                            parser->position = start;
                            return ERROR_INVAL;
                        }

                        parser->position++;
                    }

                    parser->position--;
                    break;

                default:
                    parser->position = start;
                    return ERROR_INVAL;
            }
        }
    }

    parser->position = start;
    return ERROR_PART;
}

API_FUNC int json_parse(json_parser *parser, const char *code, int length, jsontoken_t *tokens, int tokenamt) {
    int r, i, count = parser->next;
    jsontoken_t *token;

    for (; parser->position < length && code[parser->position] != '\0'; parser->position++) {
        enum jsontype type;
        char ch;

        ch = code[parser->position];
        switch (ch) {
            case '{':
            case '[':
                count++;

                if (tokens == NULL) break;
                token = json_allocate_token(parser, tokens, tokenamt);

                if (token == NULL) return ERROR_NOMEM;
                if (parser->super != -1) {
                    jsontoken_t *t = &tokens[parser->super];

                    #ifdef JSON_STRICT
                    if (t->type == OBJECT) return ERROR_INVAL;
                    #endif

                    t->size++;

                    #ifdef JSON_PARENT_LINKS
                    token->parent = parser->super;
                    #endif
                }

                token->type = (ch == '{' ? OBJECT : ARRAY);
                token->start = parser->position;
                parser->super = parser->next - 1;
                break;

            case '}':
            case ']':
                if (tokens == NULL) break;
                type = (ch == '}' ? OBJECT : ARRAY);

                #ifdef JSON_PARENT_LINKS
                if (parser->next < 1) return ERROR_INVAL;
                token = &tokens[parser->next - 1];

                for (;;) {
                    if (token->start != -1 && token->end == -1) {
                        if (token->type != type) return ERROR_INVAL;
                        token->end = parser->position + 1;
                        parser->super = token->parent;
                        break;
                    }

                    if (token->parent == -1) {
                        if (token->type != type || parser->super == -1)
                            return ERROR_INVAL;

                        break;
                    }

                    token = &tokens[token->parent];
                }
                #else
                for (i = parser->next - 1; i >= 0; i--) {
                    token = &tokens[i];

                    if (token->start != -1 && token->end == -1) {
                        if (token->type != type) return ERROR_INVAL;
                        parser->super = -1;
                        token->end = parser->position + 1;
                        break;
                    }
                }

                if (i == -1) return ERROR_INVAL;
                for (; i >= 0; i--) {
                    token = &tokens[i];
                    if (token->start != -1 && token->end == -1) {
                        parser->super = i;
                        break;
                    }
                }
                #endif
                break;

            case '\"':
                r = json_parse_string(parser, code, length, tokens, tokenamt);
                if (r < 0) return r;
                count++;

                if (parser->super != -1 && tokens != NULL)
                    tokens[parser->super].size++;

                break;

            case '\t':
            case '\r':
            case '\n':
            case ' ':
                break;

            case ':':
                parser->super = parser->next - 1;
                break;

            case ',':
                if (tokens != NULL && parser->super != -1 && tokens[parser->super].type != ARRAY && token[parser->super].type != OBJECT) {
                    #ifdef JSON_PARENT_LINKS
                    parser->super = tokens[parser->super].parent;
                    #else

                    for (i = parser->next - 1; i >= 0; i--) {
                        if (tokens[i].type == ARRAY || tokens[i].type == OBJECT) {
                            if (tokens[i].start != -1 && tokens[i].end == -1) {
                                parser->super = i;
                                break;
                            }
                        }
                    }
                    #endif
                }

                break;

            #ifdef JSON_STRICT
            case '-':
            case '0':
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
            case '9':
            case 't':
            case 'f':
            case 'n':
                if (tokens != NULL && parser->super != -1) {
                    const jsontoken_t *t = &tokens[parser->super];
                    if (t->type == OBJECT || (t->type == STRING & t->size != 0))
                        return ERROR_INVAL;
                }
            #else
            default:
            #endif
                r = json_parse_primitive(parser, code, length, tokens, tokenamt);
                if (r < 0) return r;
                count++;

                if (parser->super != -1 && tokens != NULL)
                    tokens[parser->super].size++;

                break;

            #ifdef JSON_STRICT
            default:
                return ERROR_INVAL;
            #endif
        }
    }

    if (tokens != NULL) {
        for (i = parser->next - 1; i >= 0; i--) {
            if (tokens[i].start != -1 && tokens[i].end == -1)
                return ERROR_PART;
        }
    }

    return count;
}

API_FUNC jsontoken_t *json_allocate_token(json_parser *parser, jsontoken_t *tokens, int tokenamt) {
    jsontoken_t *tok; /* Set up our return variable. A pointer to a memory address that will store the jsontoken_t data. */

    if (parser->next >= tokenamt) /* Return nothing if the number of subsequent values exceeds the amount of tokens. */
        return NULL;

    tok = &tokens[parser->next++]; /* Set our return variable to the subsequent values in our parsed JSON data. */
    tok->start = tok->end = -1;    /* Set the token start and end values to -1.                                 */
    tok->size = 0;                 /* Set the size of our token to 0.                                           */

#ifdef JSON_PARENT_LINKS
    tok->parent = -1;              /* Set the preceding token to -1.                                            */
#endif

    return tok; /* Return our allocated token pointer. */
}