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

int popIntegerStack(Stack* s, int* dptr) {
    if (s->top == -1) {
        return 0;
    }

    *dptr = s->data[s->top--];
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
    Stack* stack1 = createIntegerStack(stackSize);
    Stack* stack2 = createIntegerStack(stackSize);

    if (stack1 == NULL || stack2 == NULL) {
        printf("Failed to create stacks.\n");
        return 1;
    }

    printf("Pushing elements onto the stacks:\n");
    int inputVal;
    while (1) {
        if (!isIntegerStackFull(stack1)) {
            printf("Enter an integer: ");
            if (scanf("%d", &inputVal) != 1) {
                printf("Invalid input.\n");
                break;
            }

            if (!pushIntegerStack(stack1, inputVal)) {
                if (!pushIntegerStack(stack2, inputVal)) {
                    printf("Both stacks are full. Stopping input.\n");
                    break;
                }
            }
        } else if (!isIntegerStackFull(stack2)) {
            printf("Enter an integer: ");
            if (scanf("%d", &inputVal) != 1) {
                printf("Invalid input.\n");
                break;
            }

            if (!pushIntegerStack(stack2, inputVal)) {
                printf("Stack 2 is full. Stopping input.\n");
                break;
            }
        } else {
            printf("Both stacks are full. Stopping input.\n");
            break;
        }
    }

    printf("\nPopping elements from stack 2:\n");
    int poppedVal;
    while (popIntegerStack(stack2, &poppedVal)) {
        printf("Popped from stack 2: %d\n", poppedVal);
    }

    printf("\nPopping elements from stack 1:\n");
    while (popIntegerStack(stack1, &poppedVal)) {
        printf("Popped from stack 1: %d\n", poppedVal);
    }

    if (isIntegerStackEmpty(stack1)) {
        printf("Stack 1 is empty.\n");
    }

    if (isIntegerStackEmpty(stack2)) {
        printf("Stack 2 is empty.\n");
    }

    freeIntegerStack(stack1);
    freeIntegerStack(stack2);
    return 0;
}