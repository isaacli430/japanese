#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

typedef struct {
    char *value;
    void *next;
} Node;

Node *head = NULL;

Node *getNode(int index) {

    Node *currNode = head;

    int i;
    for (i = 0; i < index; i++) {
        if (currNode == NULL)
            return NULL;
        
        currNode = currNode->next;
    }

    
    printf("hi\n");
    return currNode;
}

int addNode(Node *node, int index) {
    Node *currNode = head;
    // Node node;
    // node.value = malloc(strlen(value) + 1);
    // strcpy(node.value, value);
    // node.next = NULL;

    if (head == NULL) {
        if (index != -1 && index != 0)
            return -1;
        
        head = node;
        return 0;
    }

    if (index == -1) {
        while (currNode != NULL) {
            currNode = currNode->next;
        }
    } else {
        int i;
        for (i = 0; i < index; i++) {
            if (currNode == NULL)
                return -1;
            
            currNode = currNode->next;
        }

        if (currNode->next != NULL) {
            node->next = currNode->next;
        }
    }

    currNode->next = node;
    return 0;
    
}

void freeList() {
   Node* tmp;

   while (head != NULL)
    {
       tmp = head;
       head = head->next;
       free(tmp->value);
       free(tmp);
    }

}

// void parse(char *file_contents) {
//     char* token = strtok(str, "\n");

//     char** lines;

//     while (token != NULL) {
//         printf("%s\n", token);
//         token = strtok(NULL, " - ");
//     }
// }

int main(int argc, char **argv) {
    setlocale(LC_ALL, ".");

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

    // parse(file_contents);

    Node node1;
    node1.value = malloc(6);
    strcpy(node1.value, "hello");

    printf("%d\n", addNode(&node1, -1));

    printf("%s\n", head->value);
    // printf("%d\n", addNode(node2, -1));

    Node *gotNode = getNode(0);
    printf("%s\n", gotNode->value);
    // printf("%s\n", );



    free(gotNode);
    free(file_contents);
    fclose(fptr);
    freeList();
}