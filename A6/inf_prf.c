#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX 100

char stack[MAX];
int top = -1;

void push(char item) {
    if (top >= MAX - 1) {
        printf("Stack Overflow\n");
        exit(1);
    }
    top++;
    stack[top] = item;
}

char pop() {
    if (top < 0) {
        printf("Stack Underflow\n");
        exit(1);
    }
    char item = stack[top];
    top--;
    return item;
}

int precedence(char op) {
    if (op == '^')
        return 3;
    else if (op == '*' || op == '/')
        return 2;
    else if (op == '+' || op == '-')
        return 1;
    else
        return 0;
}

int isOperator(char op) {
    return (op == '^' || op == '*' || op == '/' || op == '+' || op == '-');
}

int isDigit(char c) {
    return (c >= '0' && c <= '9');
}

void reverseString(char *str) {
    int len = strlen(str);
    for (int i = 0, j = len - 1; i < j; i++, j--) {
        char temp = str[i];
        str[i] = str[j];
        str[j] = temp;
    }
}

void infixToPrefix(char *infix, char *prefix) {
    int i = 0, j = 0;
    char temp;
    top = -1;

    reverseString(infix);

    while (infix[i] != '\0') {
        if (isspace(infix[i])) {
            i++;
        } else if (isDigit(infix[i])) {
            while (isDigit(infix[i])) {
                temp = infix[i++];
                push(temp);
            }
            prefix[j++] = ' ';
            while (top >= 0) {
                prefix[j++] = pop();
            }
        } else if (!isOperator(infix[i]) && infix[i] != '(' && infix[i] != ')') {
            prefix[j++] = infix[i++];
        } else {
            if (infix[i] == ')') {
                push(infix[i++]);
            } else if (infix[i] == '(') {
                while (top >= 0 && stack[top] != ')') {
                    prefix[j++] = pop();
                    prefix[j++] = ' ';
                }
                if (top >= 0 && stack[top] == ')') {
                    pop();
                } else {
                    printf("Mismatched parentheses!\n");
                    exit(1);
                }
                i++;
            } else {
                while (top >= 0 && precedence(stack[top]) >= precedence(infix[i])) {
                    prefix[j++] = pop();
                    prefix[j++] = ' ';
                }
                push(infix[i++]);
            }
        }
    }

    while (top >= 0) {
        if (stack[top] == '(' || stack[top] == ')') {
            printf("Mismatched parentheses!\n");
            exit(1);
        }
        prefix[j++] = pop();
        prefix[j++] = ' ';
    }

    prefix[j] = '\0';
    reverseString(prefix);
}

int main() {
    char infix[MAX], prefix[MAX];

    printf("Enter an infix expression: ");
    fgets(infix, MAX, stdin);
    infix[strlen(infix) - 1] = '\0';

    infixToPrefix(infix, prefix);

    printf("Infix Expression: %s\n", infix);
    printf("Prefix Expression: %s\n", prefix);

    return 0;
}
