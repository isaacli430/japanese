#ifndef common_h
#define common_h

#include "common.h"

#endif

#include "parser.h"
#include <time.h>

int main(int argc, char **argv) {

    clock_t t;
    t = clock();

    FILE *fptr = fopen(argv[1], "r");
    if (fptr == NULL) {
        perror("open");
        return -1;
    }
    
    if (fseek(fptr, 0, SEEK_END) != 0) {
        perror("fseek");
        return -1;
    }

    long filesize = ftell(fptr);

    if (fseek(fptr, 0, SEEK_SET) != 0) {
        perror("fseek");
        return -1;
    }
    
    char *file_contents = malloc(filesize + 1);

    fread(file_contents, filesize, 1, fptr);
    file_contents[filesize] = 0;



    uint16_t line_count = 0;


    IdentifierArray identifier_array;
    init_identifier_array(&identifier_array, 4);

    char *print_identifier = (char *)malloc(10);
    if (print_identifier == NULL)
        exit(1);

    strncpy(print_identifier, "を印刷", 10);
    write_identifier(&identifier_array, print_identifier);


    ValueArray value_array;
    init_value_array(&value_array, 4);

    ValueData data;

    data.bool_value = false;
    write_value(&value_array, BOOLEAN, data);

    data.bool_value = true;
    write_value(&value_array, BOOLEAN, data);

    OperationArray operation_array;


    if (parse(file_contents, 0, &line_count, &identifier_array, &value_array, &operation_array) != 0) {
        free_value_array(&value_array);
        free_identifier_array(&identifier_array);
        free(file_contents);
        fclose(fptr);
        printf("error found\n");
        return -1;
    }

    print_value_array(&value_array);
    print_identifier_array(&identifier_array);
    free_identifier_array(&identifier_array);
    free_value_array(&value_array);
    free(file_contents);
    fclose(fptr);

    t = clock() - t;
    double time_taken = ((double)t)/CLOCKS_PER_SEC;
    printf("total time: %lfs\n", time_taken);

    return 0;
}