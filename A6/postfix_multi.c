#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX 100

int stack[MAX];
int top = -1;

void push(int item) {
  if(top >= MAX-1) {
    printf("Stack Overflow\n");
    return;
  }
  top++;
  stack[top] = item;
}

int pop() {
  if(top < 0) {
    printf("Stack Underflow\n");
    return 0;
  }
  int item = stack[top];
  top--;
  return item;
} 

int operate(int a, int b, char op) {
  switch(op) {
    case '+': return a + b;
    case '-': return a - b; 
    case '*': return a * b;
    case '/': return a / b;
  }
}

int evaluatePostfix(char *exp) {
  int i = 0;
  
  while (exp[i] != '\0') {
    if (isdigit(exp[i])) {
      int operand = 0;
      while (isdigit(exp[i])) {
        operand = (operand * 10) + (exp[i] - '0');
        i++;
      }
      push(operand);
    } else if (exp[i] == ' ') {
      // Skip spaces
      i++;
    } else {
      int val2 = pop();
      int val1 = pop();
      
      int result = operate(val1, val2, exp[i]);
      
      push(result);
      i++;
    }
  }
  
  return stack[top];
}

int main() {
  char exp[] = "123 456 + 78 *";
  int result = evaluatePostfix(exp);
  printf("Result is: %d\n", result);
  return 0;
}
