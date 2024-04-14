#ifndef common_h
#define common_h

#include "common.h"

#endif

#include "parser.h"

int main(int argc, char **argv) {

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

    if (parse(file_contents) != 0) {
        free(file_contents);
        fclose(fptr);
        return -1;
    }

    free(file_contents);
    fclose(fptr);

    return 0;
}