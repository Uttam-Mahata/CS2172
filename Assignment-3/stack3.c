
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char* data;
    int size;
    int top;
} Stack;

Stack* createCharStack(int stackSize) {
    Stack* newStack = (Stack*)malloc(sizeof(Stack));
    if (newStack == NULL) {
        return NULL;
    }

    newStack->data = (char*)malloc(stackSize * sizeof(char));
    if (newStack->data == NULL) {
        free(newStack);
        return NULL;
    }

    newStack->size = stackSize;
    newStack->top = -1;
    return newStack;
}

int pushCharStack(Stack* s, char c) {
    if (s->top == s->size - 1) {
        return 0;
    }

    s->data[++s->top] = c;
    return 1;
}

int popCharStack(Stack* s, char* cp) {
    if (s->top == -1) {
        return 0;
    }

    *cp = s->data[s->top--];
    return 1;
}

int isCharStackFull(Stack* s) {
    return (s->top == s->size - 1);
}

int isCharStackEmpty(Stack* s) {
    return (s->top == -1);
}

int freeCharStack(Stack* s) {
    if (s != NULL) {
        free(s->data);
        free(s);
        return 1;
    }
    return 0;
}

int main() {
    char expression[] = "{ ( A + B ) * C } + D";
    int expressionLength = strlen(expression);
    Stack* parenStack = createCharStack(expressionLength);

    if (parenStack == NULL) {
        printf("Failed to create stack.\n");
        return 1;
    }

    int balanced = 1;
    for (int i = 0; i < expressionLength; i++) {
        char c = expression[i];
        if (c == '{' || c == '[' || c == '(') {
            pushCharStack(parenStack, c);
        } else if (c == '}' || c == ']' || c == ')') {
            char poppedChar;
            if (!popCharStack(parenStack, &poppedChar)) {
                balanced = 0; // Unmatched closing parenthesis
                break;
            }

            if ((c == '}' && poppedChar != '{') ||
                (c == ']' && poppedChar != '[') ||
                (c == ')' && poppedChar != '(')) {
                balanced = 0; // Mismatched parenthesis types
                break;
            }
        }
    }

    if (balanced && isCharStackEmpty(parenStack)) {
        printf("Expression is balanced.\n");
    } else {
        printf("Expression is not balanced.\n");
    }

    freeCharStack(parenStack);
    return 0;
}
