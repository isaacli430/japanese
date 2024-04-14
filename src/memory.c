#ifndef common_h
#define common_h
#include "common.h"
#endif

void initTokenArray(TokenArray *token_array) {
    token_array->count = 0;
    token_array->capacity = 0;
    token_array->data = NULL;
}

void writeToken(TokenArray *token_array, Token token) {
    if (token_array->capacity == 0) {
        token_array->data = malloc(2*sizeof(Token));
        if (token_array->data == NULL) 
            exit(1);

        token_array->data[0] = token;

        token_array->count++;
        token_array->capacity += 2;
        
    } else if (token_array->count == token_array->capacity - 1) {
        token_array->data = realloc(token_array->data, 2*sizeof(Token)*token_array->capacity);
        if (token_array->data == NULL) 
            exit(1);

        token_array->data[token_array->count] = token;

        token_array->count++;
        token_array->capacity *= 2;
    } else {
        token_array->data[token_array->count] = token;
        token_array->count++;
    }
}

void freeTokenArray(TokenArray *token_array) {
    free(token_array->data);
    token_array->data = NULL;
    token_array->count = 0;
    token_array->capacity = 0;
}

void printTokenArray(TokenArray *token_array) {
    printf("{count: %d; capacity: %d; ", token_array->count, token_array->capacity);
    int i;
    for (i = 0; i < token_array->count; i++) {
        printf("(");
        switch (token_array->data[i].type) {

            case STR:
                printf(" STR: %d ", token_array->data[i].value);
                break;

            case INT:
                printf(" INT: %d ", token_array->data[i].value);
                break;

            case FLOAT:
                printf(" FLOAT: %d ", token_array->data[i].value);
                break;

            case IDENTIFIER:
                printf(" IDENTIFIER: %d ", token_array->data[i].value);
                break;

            case OPEN_SQ:
                printf("\"[\"");
                break;

            case CLOSE_SQ:
                printf("\"]\"");
                break;
            
            case OPEN_PAREN:
                printf("\"(\"");
                break;

            case CLOSE_PAREN:
                printf("\")\"");
                break;

            case OPEN_CURL:
                printf("\"{\"");
                break;

            case CLOSE_CURL:
                printf("\"}\"");
                break;

            case PLUS:
                printf("\"+\"");
                break;

            case MINUS:
                printf("\"-\"");
                break;

            case MULT:
                printf("\"*\"");
                break;

            case DIVIDE:
                printf("\"/\"");
                break;

            case NOT_EQUAL:
                printf("\"!=\"");
                break;

            case NOT:
                printf("\"!\"");
                break;

            case EQUAL:
                printf("\"==\"");
                break;

            case COMMA:
                printf("\",\"");
                break;

            case TRU:
                printf(" TRUE ");
                break;

            case FAL:
                printf(" FALSE ");
                break;

            case FUNC:
                printf(" FUNC ");
                break;

            case KAGIRI:
                printf(" かぎり ");
                break;

            case NO:
                printf(" の ");
                break;

            case HA:
                printf(" は ");
                break;

            default:
                printf("UNKNOWN TYPE");
                break;
        }
    printf(")");
    }
    printf("}\n");
}


// void initTokenArray(TokenArray *token_array) {
//     token_array->count = 0;
//     token_array->capacity = 0;
//     token_array->data = NULL;
// }

// void writeToken(TokenArray *token_array, Token token) {
//     if (token_array->capacity == 0) {
//         token_array->data = malloc(2*sizeof(Token));
//         if (token_array->data == NULL) 
//             exit(1);

//         token_array->data[0] = token;

//         token_array->count++;
//         token_array->capacity += 2;
        
//     } else if (token_array->count == token_array->capacity - 1) {
//         token_array->data = realloc(token_array->data, 2*sizeof(Token)*token_array->capacity);
//         if (token_array->data == NULL) 
//             exit(1);

//         token_array->data[token_array->count] = token;

//         token_array->count++;
//         token_array->capacity *= 2;
//     } else {
//         token_array->data[token_array->count] = token;
//         token_array->count++;
//     }
// }

// void freeTokenArray(TokenArray *token_array) {
//     free(token_array->data);
//     token_array->data = NULL;
//     token_array->count = 0;
//     token_array->capacity = 0;
// }