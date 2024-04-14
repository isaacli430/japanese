// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
// #include "nodes.h"

// Node *getNode(int index, Node **head) {

//     Node *currNode = *head;

//     int i;
//     for (i = 0; i < index; i++) {
//         if (currNode == NULL)
//             return NULL;
        
//         currNode = currNode->next;
//     }
//     return currNode;
// }

// int addNode(void *value, int index, int datatype, Node **head) {
//     Node *currNode = *head;
//     Node *node = malloc(sizeof(Node));
//     node->next = NULL;
//     node->type = datatype;
//     node->value = value;

//     if (currNode == NULL) {
//         if (index != -1 && index != 0) {
//             free(node->value);
//             free(node);
//             return -1;
//         }        
        
//         *head = node;
//         return 0;
//     }

//     if (index == -1) {
//         while (currNode->next != NULL) {
//             currNode = currNode->next;
//         }
//     } else {
//         int i;
//         for (i = 0; i < index - 1; i++) {
//             if (currNode == NULL) {
//                 free(node->value);
//                 free(node);
//                 return -1;
//             }      
            
//             currNode = currNode->next;
//         }

//         if (currNode == NULL) {
//             free(node->value);
//             free(node);
//             return -1;
//         }      

//         if (currNode->next != NULL) {
//             node->next = currNode->next;
//         }
//     }

//     currNode->next = node;
//     return 0;
// }

// void freeList(Node *head) {
//     Node *tmp;

//     while (head != NULL) {
//         tmp = head;
//         head = head->next;

//         switch (tmp->type) {
            
//             case LIST:
//                 freeList(tmp->value);
//                 break;

//             case CLOSE_SQ:      
//             case OPEN_PAREN:
//             case CLOSE_PAREN:
//             case OPEN_CURL:
//             case CLOSE_CURL:
//             case DA:
//             case TOIU:
//             case KAGIRI:
//             case HA:
//                 break;

//             default:
//                 free(tmp->value);
//                 break;
//         }

//         free(tmp);
//     }

// }

// int removeNode(Node **head) {
//     if (*head == NULL)
//         return -1;

//     Node *tmp = *head;
//     *head = (*head)->next;

//     switch (tmp->type) {
        
//         case LIST:
//             freeList(tmp->value);
//             break;

//         default:
//             free(tmp->value);
//             break;
//     }
//     free(tmp);
//     return 0;
// }

// void printElem(void *value, int datatype) {
//     printf("{");
//     switch (datatype) {
//         case LIST:
//             printf("LIST: ");
//             printVerbose((Node *)value);
//             break;

//         case TOKEN:
//             printf("TOKEN: \"%s\"", (char *)value);
//             break;

//         case STR:
//             printf("STR: \"%s\"", (char *)value);
//             break;

//         case INT:
//             printf("INT: %d", *(int *)value);
//             break;

//         case FLOAT:
//             printf("FLOAT: %lf", *(double *)value);
//             break;

//         case IDENTIFIER:
//             printf("IDENTIFIER: \"%s\"", (char *)value);
//             break;

//         case OPEN_SQ:
//             printf("\"[\"");
//             break;

//         case CLOSE_SQ:
//             printf("\"]\"");
//             break;
        
//         case OPEN_PAREN:
//             printf("\"(\"");
//             break;

//         case CLOSE_PAREN:
//             printf("\")\"");
//             break;

//         case OPEN_CURL:
//             printf("\"{\"");
//             break;

//         case CLOSE_CURL:
//             printf("\"}\"");
//             break;

//         case DA:
//             printf(" だ ");
//             break;

//         case TOIU:
//             printf(" という ");
//             break;

//         case KAGIRI:
//             printf(" かぎり ");
//             break;

//         case HA:
//             printf(" は ");
//             break;

//         default:
//             printf("UNKNOWN TYPE");
//             break;
//     }
//     printf("}");
// }

// void printVerbose(Node *head) {
//     Node *currNode = head;
//     printf("(");

//     if (currNode != NULL) {
//         printElem(currNode->value, currNode->type);
//         currNode = currNode->next;
//         while (currNode != NULL) {
//             printf(", ");
//             printElem(currNode->value, currNode->type);
//             currNode = currNode->next;
//         }
//     }
//     printf(")");
// }
