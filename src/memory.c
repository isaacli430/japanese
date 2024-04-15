#ifndef common_h
#define common_h
#include "common.h"
#endif

#define INIT_ARRAY(array, new_capacity, type) ({                                \
    if ((new_capacity) <= 0) {                                                  \
        array->data = NULL;                                                     \
    } else {                                                                    \
        array->data = malloc(new_capacity*sizeof(type));                        \
    }                                                                           \
    array->count = 0;                                                           \
    array->capacity = new_capacity;                                             \
})

#define WRITE_ARRAY(array, value, type) ({                                      \
    if (array->count >= array->capacity - 1) {                                  \
        if (array->capacity == 0) {                                             \
            array->capacity++;                                                  \
        }                                                                       \
        array->data = realloc(array->data, 2*sizeof(type)*array->capacity);     \
        if (array->data == NULL) {                                              \
            exit(1);                                                            \
        }                                                                       \
        array->capacity *= 2;                                                   \
    }                                                                           \
    array->data[array->count] = value;                                          \
    array->count++;                                                             \
})

#define FREE_ARRAY(array) ({                                                    \
    free(array->data);                                                          \
    array->data = NULL;                                                         \
    array->count = 0;                                                           \
    array->capacity = 0;                                                        \
})

void init_token_array(TokenArray *token_array) {
    INIT_ARRAY(token_array, 0, Token);
}

void write_token(TokenArray *token_array, Token token) {
    WRITE_ARRAY(token_array, token, Token);
}

void remove_token(TokenArray *token_array, uint16_t index, uint16_t remove_count) {
    if (index + remove_count > token_array->count)
        return;

    token_array->count -= remove_count;
    for (index; index < token_array->count; index++)
        token_array->data[index] = token_array->data[index+remove_count];
}

void free_token_array(TokenArray *token_array) {
    FREE_ARRAY(token_array);
}

void print_token_array(TokenArray *token_array) {
    printf("{ TOKEN ARRAY | count: %d; capacity: %d; ", token_array->count, token_array->capacity);
    int i;
    for (i = 0; i < token_array->count; i++) {
        switch (token_array->data[i].type) {

            case STR:
                printf("( STR: %d )", token_array->data[i].position);
                break;

            case INT:
                printf("( INT: %d )", token_array->data[i].position);
                break;

            case FLOAT:
                printf("( FLOAT: %d )", token_array->data[i].position);
                break;

            case LOCAL_IDENTIFIER:
                printf("( LOCAL IDENTIFIER: %d )", token_array->data[i].position);
                break;

            case ENCLOSING_IDENTIFIER:
                printf("( ENCLOSING IDENTIFIER: %d )", token_array->data[i].position);
                break;

            case BOOLEAN:
                printf("( BOOL: %d )", token_array->data[i].position);
                break;

            case OPEN_SQ:
                printf("( \"[\" )");
                break;

            case CLOSE_SQ:
                printf("( \"]\" )");
                break;
            
            case OPEN_PAREN:
                printf("( \"(\" )");
                break;

            case CLOSE_PAREN:
                printf("( \")\" )");
                break;

            case OPEN_CURL:
                printf("( \"{\" )");
                break;

            case CLOSE_CURL:
                printf("( \"}\" )");
                break;

            case PLUS:
                printf("( \"+\" )");
                break;

            case MINUS:
                printf("( \"-\" )");
                break;

            case MULT:
                printf("( \"*\" )");
                break;

            case DIVIDE:
                printf("( \"/\" )");
                break;

            case NOT_EQUAL:
                printf("( \"!=\" )");
                break;

            case NOT:
                printf("( \"!\" )");
                break;

            case EQUAL:
                printf("( \"==\" )");
                break;

            case COMMA:
                printf("( \",\" )");
                break;

            case FUNC:
                printf("( FUNC )");
                break;

            case KAGIRI:
                printf("( かぎり )");
                break;

            case NO:
                printf("( の )");
                break;

            case HA:
                printf("( は )");
                break;

            default:
                printf("( UNKNOWN TYPE )");
                break;
        }
    }
    printf(" }\n");
}


void init_value_array(ValueArray *value_array, uint16_t capacity) {
    INIT_ARRAY(value_array, capacity, Value);
}

void write_value(ValueArray *value_array, uint8_t type, ValueData data) {
    Value value = { type = type, data = data };

    WRITE_ARRAY(value_array, value, Value);
}

void free_value_array(ValueArray *value_array) {
    for (int i = 0; i < value_array->count; i++) {
        if (value_array->data[i].type == STR)
            free(value_array->data[i].data.str_value.pointer);
    }

    FREE_ARRAY(value_array);
}

void print_value_array(ValueArray *value_array) {
    printf("{ VALUE ARRAY | count: %d; capacity: %d; ", value_array->count, value_array->capacity);
    for (int i = 0; i < value_array->count; i++) {
        switch (value_array->data[i].type) {
            case BOOLEAN:
                printf("( BOOLEAN: ");
                if (value_array->data[i].data.bool_value == false)
                    printf("FALSE )");
                
                else
                    printf("TRUE )");

                break;

            case INT:
                printf("( INT: %d )", value_array->data[i].data.int_value);
                break;

            case FLOAT:
                printf("( FLOAT: %lf )", value_array->data[i].data.double_value);
                break;

            case STR:
                printf("( STR: %s )", value_array->data[i].data.str_value.pointer);
                break;

            default:
                printf("( UNKNOWN TYPE )");
        }
    }

    printf(" }\n");
}


void init_identifier_array(IdentifierArray *identifier_array, uint16_t capacity) {
    INIT_ARRAY(identifier_array, capacity, char *);
}

void write_identifier(IdentifierArray *identifier_array, char *identifier) {
    WRITE_ARRAY(identifier_array, identifier, char *);
}

void truncate_identifiers_from_index(IdentifierArray *identifier_array, uint16_t index) {
    for (int i = index; i < identifier_array->count; i++)
        free(identifier_array->data[i]);
        
    identifier_array->count = index;
}

void free_identifier_array(IdentifierArray *identifier_array) {
    for (int i = 0; i < identifier_array->count; i++)
        free(identifier_array->data[i]);

    FREE_ARRAY(identifier_array);
}

void print_identifier_array(IdentifierArray *identifier_array) {
    printf("{ IDENTIFIER ARRAY | count: %d; capacity: %d; ", identifier_array->count, identifier_array->capacity);

    for (int i = 0; i < identifier_array->count; i++)
        printf("( %s )", identifier_array->data[i]);

    printf(" }\n");
}