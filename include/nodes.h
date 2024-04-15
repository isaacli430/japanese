#ifndef common_h
#define common_h
#include "common.h"
#endif

enum Types {
    STR,
    INT,
    FLOAT,
    BOOLEAN,
    OBJECT,
    ENCLOSING_IDENTIFIER,
    LOCAL_IDENTIFIER,
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
    FUNC,
    KAGIRI,
    NO,
    HA
};

typedef struct {
    uint8_t type;
    uint16_t position;
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

typedef union {
    Object *obj_ptr;
    int int_value;
    double double_value;
    bool bool_value;

    struct {
        bool is_constant;
        char *pointer;
    } str_value;
} ValueData;

typedef struct {
    uint8_t type;
    ValueData data;
} Value;

typedef struct {
    uint16_t count;
    uint16_t capacity;
    Value *data;
} ValueArray;

typedef struct {
    uint16_t count;
    uint16_t capacity;
    char **data;
} IdentifierArray;

typedef struct {
    uint8_t type;
    uint8_t value;
} Operation;

typedef struct {
    uint16_t count;
    uint16_t capacity;
    Operation *data;
} OperationArray;

void init_token_array(TokenArray *token_array);
void write_token(TokenArray *token_array, Token token);
void remove_token(TokenArray *token_array, uint16_t index, uint16_t remove_count);
void free_token_array(TokenArray *token_array);
void print_token_array(TokenArray *token_array);


void init_value_array(ValueArray *value_array, uint16_t capacity);
void write_value(ValueArray *value_array, uint8_t type, ValueData data);
void free_value_array(ValueArray *value_array);
void print_value_array(ValueArray *value_array);

void init_identifier_array(IdentifierArray *identifier_array, uint16_t capacity);
void write_identifier(IdentifierArray *identifier_array, char *identifier);
void truncate_identifiers_from_index(IdentifierArray *identifier_array, uint16_t index);
void free_identifier_array(IdentifierArray *identifier_array);
void print_identifier_array(IdentifierArray *identifier_array);

// Node *getNode(int index, Node **head);
// int addNode(void *value, int index, int datatype, Node **head);
// void freeList(Node *head);
// int removeNode(Node **head);
// void printVerbose(Node *head);

// typedef struct {
//     void *value;
//     void *next;
//     enum Types type;
// } Node;