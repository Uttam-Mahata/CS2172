#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct intNode {
    int element;
    struct intNode *next;
};

struct intNode *addIntNodeSorted(struct intNode *start, int elem) {
    struct intNode *newNode = (struct intNode *)malloc(sizeof(struct intNode));
    newNode->element = elem;
    newNode->next = NULL;

    if (start == NULL || elem < start->element) {
        newNode->next = start;
        return newNode;
    }

    struct intNode *current = start;
    while (current->next != NULL && current->next->element < elem) {
        current = current->next;
    }

    newNode->next = current->next;
    current->next = newNode;
    return start;
}

int isPresentIntNodeSorted(struct intNode *start, int elem) {
    int position = 1;
    struct intNode *current = start;

    while (current != NULL) {
        if (current->element == elem) {
            return position;
        }
        current = current->next;
        position++;
    }

    return 0;
}

struct intNode *deleteIntNodeSorted(struct intNode *start, int elem) {
    if (start == NULL) {
        return NULL;
    }

    if (start->element == elem) {
        struct intNode *temp = start;
        start = start->next;
        free(temp);
        return start;
    }

    struct intNode *current = start;
    while (current->next != NULL && current->next->element != elem) {
        current = current->next;
    }

    if (current->next != NULL) {
        struct intNode *temp = current->next;
        current->next = current->next->next;
        free(temp);
    }

    return start;
}

struct intNode *freeIntNodeSorted(struct intNode *start) {
    while (start != NULL) {
        struct intNode *temp = start;
        start = start->next;
        free(temp);
    }
    return NULL;
}

struct intNode *reverseIntNodeSorted(struct intNode *start) {
    struct intNode *prev = NULL;
    struct intNode *current = start;
    struct intNode *nextNode;

    while (current != NULL) {
        nextNode = current->next;
        current->next = prev;
        prev = current;
        current = nextNode;
    }

    return prev;
}

void updateIntNode(struct intNode *start) {
    srand(time(NULL));
    struct intNode *current = start;

    while (current != NULL) {
        int randomValue = rand() % 10;
        current->element += randomValue;
        current = current->next;
    }
}

struct intNode *sortIntNode(struct intNode *start) {
    if (start == NULL || start->next == NULL) {
        return start;
    }

    struct intNode *sortedList = NULL;
    while (start != NULL) {
        struct intNode *current = start;
        start = start->next;

        if (sortedList == NULL || current->element <= sortedList->element) {
            current->next = sortedList;
            sortedList = current;
        } else {
            struct intNode *temp = sortedList;
            while (temp->next != NULL && temp->next->element < current->element) {
                temp = temp->next;
            }
            current->next = temp->next;
            temp->next = current;
        }
    }

    return sortedList;
}

struct intNode *mergeIntNodeSorted(struct intNode *start1, struct intNode *start2) {
    struct intNode *mergedList = NULL;

    while (start1 != NULL && start2 != NULL) {
        if (start1->element <= start2->element) {
            mergedList = addIntNodeSorted(mergedList, start1->element);
            start1 = start1->next;
        } else {
            mergedList = addIntNodeSorted(mergedList, start2->element);
            start2 = start2->next;
        }
    }

    while (start1 != NULL) {
        mergedList = addIntNodeSorted(mergedList, start1->element);
        start1 = start1->next;
    }

    while (start2 != NULL) {
        mergedList = addIntNodeSorted(mergedList, start2->element);
        start2 = start2->next;
    }

    freeIntNodeSorted(start1);
    freeIntNodeSorted(start2);

    return mergedList;
}

void printLL(struct intNode *start) {
    struct intNode *current = start;

    printf("Start -> ");
    while (current != NULL) {
        printf("%d -> ", current->element);
        current = current->next;
    }
    printf("NULL\n");
}

int main() {
    struct intNode *start = NULL;

    int listSize1,listSize2;
    printf("Enter the number of integers which you want to store: ");
    scanf("%d",&listSize1);
    int farrSize[listSize1];
   
    printf("Enter the value of integers which you want to store: ");
    
    for(int i = 0;i<listSize1;i++) {
        scanf("%d",&farrSize[i]);
    }

    for (int i = 0; i < listSize1; i++)
    {
        start = addIntNodeSorted(start,farrSize[i]);
    
    }

    /*start = addIntNodeSorted(start, 12);
    start = addIntNodeSorted(start, 5);
    start = addIntNodeSorted(start, 2);
    start = addIntNodeSorted(start, 11);*/

    printf("Original Linked List:\n");
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

    // start = freeIntNodeSorted(start);
    // printf("Linked List after freeing all nodes:\n");
    // printLL(start);

    start = reverseIntNodeSorted(start);
    printf("Linked List after reversing:\n");
    printLL(start);

    updateIntNode(start);
    printf("Linked List after updating elements:\n");
    printLL(start);

    start = sortIntNode(start);
    printf("Linked List after sorting in ascending order:\n");
    printLL(start);

    struct intNode *start2 = NULL;
    printf("Enter the number of integers which you want to store in list 2: ");
    scanf("%d",&listSize2);
    int sarrSize[listSize2];
    printf("Enter the value of integers which you want to store: ");
    
    for(int i = 0;i<listSize2;i++) {
        scanf("%d",&sarrSize[i]);
    }

    for (int i = 0; i < listSize2; i++)
    {
        start2 = addIntNodeSorted(start2,sarrSize[i]);
    
    }


    /*start2 = addIntNodeSorted(start2, 8);
    start2 = addIntNodeSorted(start2, 4);
    start2 = addIntNodeSorted(start2, 6);*/
    printf("Second Linked List:\n");


    printLL(start2);


    struct intNode *mergedList = mergeIntNodeSorted(start, start2);
    printf("Merged Linked List:\n");
    printLL(mergedList);

    
    mergedList = freeIntNodeSorted(mergedList);

    return 0;
}