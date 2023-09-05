#include <stdio.h>
#include <stdlib.h>
#include "linked_list.h"

struct intNode* addIntNodeSorted(struct intNode* start, int elem) {
    struct intNode* newNode = (struct intNode*)malloc(sizeof(struct intNode));
    newNode->element = elem;
    newNode->next = NULL;


    if (start == NULL || elem < start->element) {
        newNode->next = start;
        return newNode;
    }

    struct intNode* current = start;
    while (current->next != NULL && current->next->element < elem) {
        current = current->next;
    }

    newNode->next = current->next;
    current->next = newNode;
    return start;
}

int isPresentIntNodeSorted(struct intNode* start, int elem) {
    int position = 1;
    struct intNode* current = start;
    while (current != NULL) {
        if (current->element == elem) {
            return position;
        }
        current = current->next;
        position++;
    }
    return 0;
}

struct intNode* deleteIntNodeSorted(struct intNode* start, int elem) {
    if (start == NULL) {
        return NULL;
    }

    if (start->element == elem) {
        struct intNode* temp = start;
        start = start->next;
        free(temp);
        return start;
    }

    
    struct intNode* current = start;
    while (current->next != NULL && current->next->element != elem) {
        current = current->next;
    }

    if (current->next != NULL) {
        struct intNode* temp = current->next;
        current->next = current->next->next;
        free(temp);
    }

    return start;
}

void printLL(struct intNode* start) {
    printf("Start -> ");
    struct intNode* current = start;
    while (current != NULL) {
        printf("%d -> ", current->element);
        current = current->next;
    }
    printf("NULL\n");
}


int main() {
    struct intNode* start = NULL;
    int listSize;
    printf("Enter the number of integers which you want to store: ");
    scanf("%d",&listSize);
    int arrSize[listSize];
    printf("Enter the value of integers which you want to store: ");
    
    for(int i = 0;i<listSize;i++) {
        scanf("%d",&arrSize[i]);
    }

    for (int i = 0; i < listSize; i++)
    {
        start = addIntNodeSorted(start,arrSize[i]);
    
    }
    
    // start = addIntNodeSorted(start, 12);
    // start = addIntNodeSorted(start, 5);
    // start = addIntNodeSorted(start, 11);
    // start = addIntNodeSorted(start, 2);

    printLL(start);

    int searchElement;
    printf("Enter the element which you want you search: ");
    scanf("%d", &searchElement);
    int position = isPresentIntNodeSorted(start, searchElement);
    if (position != 0) {
        printf("%d is present at position %d\n", searchElement, position);
    } else {
        printf("%d is not present.\n", searchElement);
    }

    int delElement;
    printf("Enter the element which you want you delete: ");
    scanf("%d", &delElement);
    start = deleteIntNodeSorted(start, delElement);
    printf("Linked list after deletion:\n ");

    printLL(start);

    return 0;
}
