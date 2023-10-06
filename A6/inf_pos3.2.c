#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

void infixToPostfix(char *infix, char *postfix) {
  int i = 0, j = 0;
  char temp;
  top = -1; // Reset the stack

  while (infix[i] != '\0') {
    if (!isOperator(infix[i]) && infix[i] != '(' && infix[i] != ')') {
      postfix[j++] = infix[i++];
    } else {
      if (infix[i] == '(') {
        push(infix[i++]);
      } else if (infix[i] == ')') {
        while (top >= 0 && stack[top] != '(') {
          postfix[j++] = pop();
        }
        if (top >= 0 && stack[top] == '(') {
          pop();
        } else {
          printf("Mismatched parentheses!\n");
          exit(1);
        }
        i++;
      } else { 
        while (top >= 0 && precedence(stack[top]) >= precedence(infix[i])) {
          postfix[j++] = pop();
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
    postfix[j++] = pop();
  }

  postfix[j] = '\0';
}

int main() {
  char infix[MAX], postfix[MAX];

  strcpy(infix, "a+b*(c^d-e)^(f+g*h)-i");

  infixToPostfix(infix, postfix);

  printf("Infix Expression: %s\n", infix);
  printf("Postfix Expression: %s\n", postfix);

  return 0;
}
