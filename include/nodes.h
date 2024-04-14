#ifndef common_h
#define common_h
#include "common.h"
#endif

enum Types {
    IDENTIFIER,
    STR,
    INT,
    FLOAT,
    OPEN_SQ,
    CLOSE_SQ,
    OPEN_PAREN,
    CLOSE_PAREN,
    OPEN_CURL,
    CLOSE_CURL,
    PLUS,
    MINUS,
    MULT,
    DIVIDE,
    COMMA,
    NOT_EQUAL,
    NOT,
    EQUAL,
    TRU,
    FAL,
    FUNC,
    KAGIRI,
    NO,
    HA
};

typedef struct {
    uint16_t count;
    uint16_t capacity;
    uint8_t *data;
} ByteArray;

typedef struct {
    uint16_t type;
    uint8_t value;
} Token;

typedef struct {
    uint16_t count;
    uint16_t capacity;
    Token *data;
} TokenArray;

typedef struct {
    uint8_t type;
    void *data;
} Object;

typedef struct {
    uint8_t type;
    union {
        Object *obj_ptr;
        int int_value;
        double double_value;
        bool bool_value;

        struct {
            bool is_constant;
            char *pointer;
        } str_value;

    } data;
} Value;

typedef struct {
    uint16_t count;
    uint16_t capacity;
    Value *value;
} ValueArray;

typedef struct {
    void *value;
    void *next;
    enum Types type;
} Node;

void printTokenArray(TokenArray *token_array);
void initTokenArray(TokenArray *token_array);
void writeToken(TokenArray *token_array, Token token);
void freeTokenArray(TokenArray *token_array);


// Node *getNode(int index, Node **head);
// int addNode(void *value, int index, int datatype, Node **head);
// void freeList(Node *head);
// int removeNode(Node **head);
// void printVerbose(Node *head);