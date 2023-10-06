#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_STACK_SIZE 100

struct Stack {
    int data[MAX_STACK_SIZE];
    int top;
};

void initialize(struct Stack *s) {
    s->top = -1;
}

void push(struct Stack *s, int value) {
    if (s->top == MAX_STACK_SIZE - 1) {
        printf("Stack overflow!\n");
        exit(1);
    }
    s->data[++s->top] = value;
}

int pop(struct Stack *s) {
    if (s->top == -1) {
        printf("Stack underflow!\n");
        exit(1);
    }
    return s->data[s->top--];
}

int evaluatePrefix(char prefix[]) {
    struct Stack s;
    initialize(&s);

    int length = strlen(prefix);
    for (int i = length - 1; i >= 0; i--) {
        if (isdigit(prefix[i])) {
            push(&s, prefix[i] - '0');
        } else {
            int operand1 = pop(&s);
            int operand2 = pop(&s);

            switch (prefix[i]) {
                case '+':
                    push(&s, operand1 + operand2);
                    break;
                case '-':
                    push(&s, operand1 - operand2);
                    break;
                case '*':
                    push(&s, operand1 * operand2);
                    break;
                case '/':
                    push(&s, operand1 / operand2);
                    break;
                default:
                    printf("Invalid operator: %c\n", prefix[i]);
                    exit(1);
            }
        }
    }

    if (s.top == 0) {
        return s.data[0];
    } else {
        printf("Invalid expression!\n");
        exit(1);
    }
}

int main() {
    char prefix[] = "+5*32";
    int result = evaluatePrefix(prefix);
    printf("Result: %d\n", result);
    return 0;
}
