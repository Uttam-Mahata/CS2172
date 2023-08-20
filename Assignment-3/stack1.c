 
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int* data;
    int size;
    int top;
} Stack;

Stack* createIntegerStack(int stackSize) {
    Stack* newStack = (Stack*)malloc(sizeof(Stack));
    if (newStack == NULL) {
        return NULL;
    }

    newStack->data = (int*)malloc(stackSize * sizeof(int));
    if (newStack->data == NULL) {
        free(newStack);
        return NULL;
    }

    newStack->size = stackSize;
    newStack->top = -1;
    return newStack;
}

int pushIntegerStack(Stack* s, int d) {
    if (s->top == s->size - 1) {
        return 0;
    }

    s->data[++s->top] = d;
    return 1;
}

int popIntegerStack(Stack* s, int* dp) {
    if (s->top == -1) {
        return 0;
    }

    *dp = s->data[s->top--];
    return 1;
}

int isIntegerStackFull(Stack* s) {
    return (s->top == s->size - 1);
}

int isIntegerStackEmpty(Stack* s) {
    return (s->top == -1);
}

int freeIntegerStack(Stack* s) {
    if (s != NULL) {
        free(s->data);
        free(s);
        return 1;
    }
    return 0;
}

int main() {
    int stackSize = 5;
    Stack* myStack = createIntegerStack(stackSize);

    if (myStack == NULL) {
        printf("Failed to create stack.\n");
        return 1;
    }

    printf("Pushing elements onto the stack:\n");
    for (int i = 1; i <= stackSize + 1; i++) {
        if (pushIntegerStack(myStack, i * 10)) {
            printf("%d pushed onto the stack.\n", i * 10);
        } else {
            printf("Stack is full. Cannot push %d.\n", i * 10);
        }
    }

    printf("\nPopping elements from the stack:\n");
    int poppedValue;
    while (popIntegerStack(myStack, &poppedValue)) {
        printf("Popped: %d\n", poppedValue);
    }

    if (isIntegerStackEmpty(myStack)) {
        printf("Stack is empty.\n");
    }

    freeIntegerStack(myStack);
    return 0;
}
