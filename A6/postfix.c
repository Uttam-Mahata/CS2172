#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<ctype.h>
struct Stack {
    int top;
    unsigned capacity;
    int* array;
};

struct Stack* createStack(unsigned capacity) {
    struct Stack* stack = (struct Stack*)malloc(sizeof(struct Stack));
    stack->capacity = capacity;
    stack->top = -1;
    stack->array = (int*)malloc(stack->capacity * sizeof(int));
    return stack;
}

int isEmpty(struct Stack* stack) {
    return stack->top == -1;
}

void push(struct Stack* stack, int item) {
    stack->array[++stack->top] = item;
}

int pop(struct Stack* stack) {
    if (!isEmpty(stack)) {
        return stack->array[stack->top--];
    }
    return -1;
}

int evaluatePostfix(char* expression) {
    struct Stack* stack = createStack(strlen(expression));
    
    for (int i = 0; expression[i]; ++i) {
        if (isdigit(expression[i])) {
            push(stack, expression[i] - '0'); // Convert character to integer
        } else {
            int operand2 = pop(stack);
            int operand1 = pop(stack);
            switch (expression[i]) {
                case '+':
                    push(stack, operand1 + operand2);
                    break;
                case '-':
                    push(stack, operand1 - operand2);
                    break;
                case '*':
                    push(stack, operand1 * operand2);
                    break;
                case '/':
                    if (operand2 != 0) {
                        push(stack, operand1 / operand2);
                    } else {
                        printf("Division by zero not possible\n");
                        exit(1);
                    }
                    break;
                default:
                    printf("Invalid operator\n");
                    exit(1);
            }
        }
    }
    
    int result = pop(stack);
    if (!isEmpty(stack)) {
        printf("wrong expression\n");
        exit(1);
    }
    
    free(stack->array);
    free(stack);
    
    return result;
}

int main() {
    char expression[100];
    printf("Enter a postfix expression: ");
    scanf("%s", expression);
    
    int result = evaluatePostfix(expression);
    printf("Result: %d\n", result);
    
    return 0;
}
