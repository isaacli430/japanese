#ifndef common_h
#define common_h

#include "common.h"

#endif

#include "kana.h"

#define HIRAGANA_MIN 0xe38181
#define HIRAGANA_MAX 0xe38296

#define KATAKANA_MIN 0xe382a1
#define KATAKANA_MAX 0xe383ba

#define KANJI_MIN 0xe4b880
#define KANJI_MAX 0xe9bda2

#define FIRST_ALLOWED_HIRAGANA KAGIRI
#define LAST_ALLOWED_HIRAGANA HA

#define KANJI_COUNT 2133

int compare_kanji(const void *a, const void *b) {
    return ( *(int *)a - *(int *)b );
}

bool is_kanji(uint32_t kanji) {
    void *result = bsearch(&kanji, ALL_KANJI, KANJI_COUNT, sizeof(uint32_t), compare_kanji);
    if (result == NULL)
        return false;

    return true;
}

int parse(char *line) {

    int line_count = 0;

    while (*line != 0) {

        TokenArray token_array;
        initTokenArray(&token_array);

        line_count++;

        // if ()

        while (*line != '\n' && *line != 0) {
            if (*line == ' ') {
                line++;
            }
            else if (*line >= 'A' && *line <= 'z') {
                uint16_t counter = 1;

                while (*(line + counter) >= 'A' && *(line + counter) <= 'z')
                    counter++;
                
                Token token = { IDENTIFIER, 0 };
                writeToken(&token_array, token);

                line += counter;
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

                Token token = { type, 0 };
                writeToken(&token_array, token);

                line += counter;

            }

            else if (*line == '"') {

                line++;
                uint16_t counter = 0;
                while (*(line + counter) != '"') {
                    if (*(line + counter) == 0 || *(line + counter) == '\n') {                   
                        freeTokenArray(&token_array);
                        return -1;
                    }

                    counter++;
                }

                // char *value = (char *)malloc(counter + 1);
                // strncpy(value, line, counter);
                
                Token token = { STR, 0 };
                writeToken(&token_array, token);

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
                writeToken(&token_array, token);
                line++;
            } 

            else if ((unsigned char)*line >= 0xe3 && (unsigned char)*line <= 0xe9) {
            
                if (strncmp(line, "、", 3) == 0) {
                    Token token = { COMMA, 0 };
                    writeToken(&token_array, token);
                    line += 3;
                }

                else if (strncmp(line, "　", 3) == 0) {
                    Token token = { COMMA, 0 };
                    writeToken(&token_array, token);
                    line += 3;
                }

                else if (strncmp(line, "真", 3) == 0) {
                    Token token = { TRU, 0 };
                    writeToken(&token_array, token);
                    line += 3;
                }

                else if (strncmp(line, "偽", 3) == 0) {
                    Token token = { FAL, 0 };
                    writeToken(&token_array, token);
                    line += 3;
                }

                else if (strncmp(line, "関数", 6) == 0) {
                    Token token = { FUNC, 0 };
                    writeToken(&token_array, token);
                    line += 3;
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

                        // unsigned char *word = malloc(counter_start + 1);
                        // strncpy(word, line, counter_start);

                        Token token = { IDENTIFIER, 0 };
                        writeToken(&token_array, token);
                        line += counter;
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
                        
                        // unsigned char *word = malloc(counter_start + 1);
                        // strncpy(word, line, counter_start);

                        Token token = { IDENTIFIER, 0 };
                        writeToken(&token_array, token);
                        line += counter;
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
                            freeTokenArray(&token_array);
                            return -1;
                        }

                        Token token = { word_type, 0 };
                        writeToken(&token_array, token);
                        line += counter;
                    }


                    else {
                        freeTokenArray(&token_array);
                        return -1;
                    }

                }


                
            }

            else {
                freeTokenArray(&token_array);
                return -1;
            }

        }
        printf("line %d: ", line_count);
        printTokenArray(&token_array);
        freeTokenArray(&token_array);

        if (*line == '\n')
            line++;
    }
    return 0;
}