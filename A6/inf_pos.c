#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include <ctype.h>

struct Stack {
    int top;
    unsigned capacity;
    char* array;
};

struct Stack* createStack(unsigned capacity) {
    struct Stack* stack = (struct Stack*)malloc(sizeof(struct Stack));
    stack->capacity = capacity;
    stack->top = -1;
    stack->array = (char*)malloc(stack->capacity * sizeof(char));
    return stack;
}

int isEmpty(struct Stack* stack) {
    return stack->top == -1;
}

char peek(struct Stack* stack) {
    return stack->array[stack->top];
}

void push(struct Stack* stack, char item) {
    stack->array[++stack->top] = item;
}

char pop(struct Stack* stack) {
    if (!isEmpty(stack)) {
        return stack->array[stack->top--];
    }
    return '\0'; 
}

int precedence(char operator) {
    switch (operator) {
        case '+':
        case '-':
            return 1;
        case '*':
        case '/':
            return 2;
        default:
            return 0;
    }
}

void infixToPostfix(char* infix, char* postfix) {
    struct Stack* stack = createStack(strlen(infix));
    int i, j;
    
    for (i = 0, j = 0; infix[i]; ++i) {
        if (isalnum(infix[i])) {
            postfix[j++] = infix[i]; 
            push(stack, ' '); 
        } else if (infix[i] == ')') {
            while (!isEmpty(stack) && peek(stack) != ' ') {
                postfix[j++] = pop(stack);
            }
            pop(stack);
        } else {
            
            while (!isEmpty(stack) && precedence(infix[i]) <= precedence(peek(stack))) {
                postfix[j++] = pop(stack);
            }
            push(stack, infix[i]);
        }
    }
    
    while (!isEmpty(stack)) {
        postfix[j++] = pop(stack); 
    }
    
    postfix[j] = '\0';
}

int main() {
    char infix[100];
    char postfix[100];
    
    printf("Enter an infix expression: ");
    scanf("%s", infix);
    
    infixToPostfix(infix, postfix);
    
    printf("Postfix expression: %s\n", postfix);
    
    return 0;
}
