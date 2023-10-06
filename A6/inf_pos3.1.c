#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

char stack[MAX];
int top = -1;

void push(char item) {
    if (top >= MAX - 1) {
        printf("Stack Overflow\n");
        exit(1); // Terminate the program on stack overflow
    }
    top++;
    stack[top] = item;
}

char pop() {
    if (top < 0) {
        printf("Stack Underflow\n");
        exit(1); // Terminate the program on stack underflow
    }
    char item = stack[top];
    top--;
    return item;
}

int precedence(char op) {
    if (op == '+' || op == '-')
        return 1;
    if (op == '*' || op == '/')
        return 2;
    return 0;
}

int isOperator(char op) {
    if (op == '+' || op == '-' || op == '*' || op == '/')
        return 1;
    else
        return 0;
}

void infixToPostfix(char *infix, char *postfix) {
    int i = 0, j = 0;
    char temp;
    top = -1; // Reset the stack

    while (infix[i] != '\0') {
        if (!isOperator(infix[i])) {
            postfix[j++] = infix[i++];
        } else {
            while (top >= 0 && precedence(stack[top]) >= precedence(infix[i])) {
                temp = pop();
                postfix[j++] = temp;
            }
            push(infix[i++]);
        }
    }

    while (top != -1) {
        temp = pop();
        postfix[j++] = temp;
    }

    postfix[j] = '\0';
}

int main() {
    char infix[MAX], postfix[MAX];

    strcpy(infix, "a+b*c-d/e");

    infixToPostfix(infix, postfix);

    printf("Postfix expression is %s\n", postfix);

    return 0;
}
