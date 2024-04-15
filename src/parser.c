#ifndef common_h
#define common_h

#include "common.h"

#endif

#include "kana.h"

#define HIRAGANA_MIN 0xe38181
#define HIRAGANA_MAX 0xe38296

#define KATAKANA_MIN 0xe382a1
#define KATAKANA_MAX 0xe383ba

#define FIRST_ALLOWED_HIRAGANA KAGIRI
#define LAST_ALLOWED_HIRAGANA HA

#define KANJI_COUNT 2133

#define INSERT_IDENTIFIER(line, counter, identifier_array, token_array) ({                  \
    unsigned char *word = malloc(counter + 1);                                              \
    strncpy(word, line, counter);                                                           \
    word[counter] = 0;                                                                      \
    uint8_t type = LOCAL_IDENTIFIER;                                                        \
    int index = get_identifier(identifier_array, word);                                     \
    uint16_t position;                                                                      \
    if (index == -1) {                                                                      \
        position = identifier_array->count - current_scope;                                 \
        write_identifier(identifier_array, word);                                           \
    } else if (index >= current_scope) {                                                    \
        position = index - current_scope;                                                   \
        free(word);                                                                         \
    } else {                                                                                \
        position = index;                                                                   \
        type = ENCLOSING_IDENTIFIER;                                                        \
        free(word);                                                                         \
    }                                                                                       \
    Token token = { type, position };                                                       \
    write_token(&token_array, token);                                                       \
    line += counter;                                                                        \
})


int compare_kanji(const void *a, const void *b) {
    return ( *(int *)a - *(int *)b );
}

bool is_kanji(uint32_t kanji) {
    void *result = bsearch(&kanji, ALL_KANJI, KANJI_COUNT, sizeof(uint32_t), compare_kanji);
    if (result == NULL)
        return false;

    return true;
}

int get_identifier(IdentifierArray *identifier_array, char *identifier) {
    int index = -1;
    for (int i = 0; i < identifier_array->count; i++) {
        if (strcmp(identifier, identifier_array->data[i]) == 0)
            index = i;
    }
    return index;
}

int parse(char *line, uint8_t parent_indent, uint16_t *line_count, IdentifierArray *identifier_array, ValueArray *value_array, OperationArray *operation_array) {

    uint16_t current_scope = identifier_array->count;

    while (*line != 0) {

        TokenArray token_array;
        init_token_array(&token_array);

        (*line_count)++;

        uint8_t indent = 0;
        while (*line == ' ') {
            if (strncmp(line, "    ", 4) == 0) {
                indent++;
                line += 4;
            } else {
                return -1;
            }
                
        }

        while (*line != '\n' && *line != 0) {
            if (*line == ' ') {
                line++;
            }
            else if (*line >= 'A' && *line <= 'z') {
                uint16_t counter = 1;

                while (*(line + counter) >= 'A' && *(line + counter) <= 'z')
                    counter++;

                INSERT_IDENTIFIER(line, counter, identifier_array, token_array);
            }

            else if (isdigit(*line)) {
                uint16_t counter = 0;
                uint8_t type = INT;
                while (isdigit(*(line + counter)))
                    counter++;

                if (*(line + counter) == '.') {
                    if (isdigit(*(line + counter + 1))) {
                        type = FLOAT;
                        counter++;

                        while (isdigit(*(line + counter)))
                            counter++;
                    }
                }

                char tmp[counter + 1];
                strncpy(tmp, line, counter);
                tmp[counter] = 0;

                uint16_t position = -1;
                ValueData data;

                if (type == INT) {
                    int tmp_int = atoi(tmp);
                    data.int_value = tmp_int;

                } else if (type == FLOAT) {
                    double tmp_double = atof(tmp);
                    data.double_value = tmp_double;
                }

                position = value_array->count;
                write_value(value_array, type, data);

                Token token = { type, position };
                write_token(&token_array, token);

                line += counter;

            }

            else if (*line == '"') {

                line++;
                uint16_t counter = 0;
                while (*(line + counter) != '"') {
                    if (*(line + counter) == 0 || *(line + counter) == '\n') {                   
                        free_token_array(&token_array);
                        return -1;
                    }

                    counter++;
                }

                char *value = (char *)malloc(counter + 1);
                if (value == NULL)
                    exit(1);

                strncpy(value, line, counter);
                value[counter] = 0;

                uint16_t position = value_array->count;

                ValueData data;
                data.str_value.is_constant = true;
                data.str_value.pointer = value;

                write_value(value_array, STR, data);
                
                Token token = { STR, position };
                write_token(&token_array, token);

                line += counter + 1;
                
            }

            else if (*line == '{' || *line == '}' || *line == '[' || *line == ']' || *line == '(' || *line == ')' || *line == '+' || *line == '-' || *line == '*' || *line == '/' || *line == ',' || *line == '.' || *line == '!' || *line == '=') {
                uint8_t type;
                switch (*line) {
                    case '{':
                        type = OPEN_CURL;
                        break;

                    case '}':
                        type = CLOSE_CURL;
                        break;

                    case '[':
                        type = OPEN_SQ;
                        break;

                    case ']':
                        type = CLOSE_SQ;
                        break;

                    case '(':
                        type = OPEN_PAREN;
                        break;

                    case '+':
                        type = PLUS;
                        break;

                    case '-':
                        type = MINUS;
                        break;

                    case '*':
                        type = MULT;
                        break;

                    case '/':
                        type = DIVIDE;
                        break;

                    case ',':
                        type = COMMA;
                        break;

                    case '.':
                        type = NO;
                        break;

                    case '!':
                        if (*(line + 1) == '=') {
                            type = NOT_EQUAL;
                            line++;
                        } else {
                            type = NOT;
                        }
                        break;

                    case '=':
                        if (*(line + 1) == '=') {
                            type = EQUAL;
                            line++;
                        } else {
                            type = HA;
                        }
                        break;

                    default:
                        type = CLOSE_PAREN;
                        break;
                }

                Token token = { type, 0 };
                write_token(&token_array, token);
                line++;
            } 

            else if ((unsigned char)*line >= 0xe3 && (unsigned char)*line <= 0xe9) {
            
                if (strncmp(line, "、", 3) == 0) {
                    Token token = { COMMA, 0 };
                    write_token(&token_array, token);
                    line += 3;
                }

                else if (strncmp(line, "　", 3) == 0) {
                    line += 3;
                }

                else if (strncmp(line, "真", 3) == 0) {
                    Token token = { BOOLEAN, 1 };
                    write_token(&token_array, token);
                    line += 3;
                }

                else if (strncmp(line, "偽", 3) == 0) {
                    Token token = { BOOLEAN, 0 };
                    write_token(&token_array, token);
                    line += 3;
                }

                else if (strncmp(line, "関数", 6) == 0) {
                    Token token = { FUNC, 0 };
                    write_token(&token_array, token);
                    line += 6;
                }

                else {

                    unsigned char kana[4] = "";
                    uint32_t kana_int = 0;

                    uint16_t counter;

                    strncpy(kana, line, 3);
                    kana[4] = 0;
                    kana_int = (uint32_t)(*kana) << 16 | (uint32_t)(*(kana + 1)) << 8 | (uint32_t)(*(kana + 2));


                    if (is_kanji(kana_int)) {
                        counter = 3;
                        while (true) {
                            strncpy(kana, line + counter, 3);
                            kana_int = (uint32_t)(*kana) << 16 | (uint32_t)(*(kana + 1)) << 8 | (uint32_t)(*(kana + 2));

                            if (is_kanji(kana_int)) {
                                counter += 3;
                            } else {
                                break;
                            }
                        }

                        INSERT_IDENTIFIER(line, counter, identifier_array, token_array);
                    }

                    else if (kana_int >= KATAKANA_MIN && kana_int <= KATAKANA_MAX) {
                        counter = 3;
                        while (true) {

                            strncpy(kana, line + counter, 3);
                            kana_int = (uint32_t)(*kana) << 16 | (uint32_t)(*(kana + 1)) << 8 | (uint32_t)(*(kana + 2));

                            if (kana_int >= KATAKANA_MIN && kana_int <= KATAKANA_MAX) {
                                counter += 3;
                            } else {
                                break;
                            }
                                
                        }
                        
                        INSERT_IDENTIFIER(line, counter, identifier_array, token_array);
                    }

                    else if (kana_int >= HIRAGANA_MIN && kana_int <= HIRAGANA_MAX) {
                        counter = 3;
                        while (true) {

                            strncpy(kana, line + counter, 3);
                            kana_int = (uint32_t)(*kana) << 16 | (uint32_t)(*(kana + 1)) << 8 | (uint32_t)(*(kana + 2));

                            if (kana_int >= HIRAGANA_MIN && kana_int <= HIRAGANA_MAX) {
                                counter += 3;
                            } else {
                                break;
                            }

                        }
                        
                        unsigned char word[counter + 1];
                        strncpy(word, line, counter);

                        word[counter] = 0;
                        
                        uint16_t k;
                        int word_type = -1;
                        for (k = FIRST_ALLOWED_HIRAGANA; k <= LAST_ALLOWED_HIRAGANA; k++) {
                            if (strcmp(ALLOWED_HIRAGANA_WORDS[k - FIRST_ALLOWED_HIRAGANA], word) == 0) {
                                word_type = k;
                                break;
                            }
                        }
                        
                        if (word_type == -1) {
                            free_token_array(&token_array);
                            return -1;
                        }

                        Token token = { word_type, 0 };
                        write_token(&token_array, token);
                        line += counter;
                    }


                    else {
                        free_token_array(&token_array);
                        return -1;
                    }
                    
                }
            }

            else {
                free_token_array(&token_array);
                return -1;
            }

        }
        printf("line %d, indent: %d: ", *line_count, indent);
        print_token_array(&token_array);
        
        free_token_array(&token_array);

        if (*line == '\n')
            line++;
    }

    print_identifier_array(identifier_array);
    truncate_identifiers_from_index(identifier_array, current_scope);
    return 0;
}