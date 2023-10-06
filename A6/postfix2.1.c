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

int evaluatePostfix(char postfix[]) {
    struct Stack s;
    initialize(&s);

    for (int i = 0; postfix[i] != '\0'; i++) {
        if (isdigit(postfix[i])) {
            push(&s, postfix[i] - '0');
        } else {
            int operand2 = pop(&s);
            int operand1 = pop(&s);

            switch (postfix[i]) {
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
                    printf("Invalid operator: %c\n", postfix[i]);
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
    char postfix[] = "53+62/*";
    int result = evaluatePostfix(postfix);
    printf("Result: %d\n", result);
    return 0;
}
