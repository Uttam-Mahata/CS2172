#include <stdio.h>
#include <stdlib.h>

struct Node {
  int id;
  struct Node* next;
};

struct Node* createCircle(int n) {
  struct Node *head, *prev, *newNode;

  head = (struct Node*)malloc(sizeof(struct Node));
  head->id = 1;
  head->next = head;

  prev = head;

  for(int i=2; i<=n; i++) {
    newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->id = i;
    newNode->next = head;
    prev->next = newNode;
    prev = newNode;
  }

  return head; 
}

void playGame(struct Node* head, int k, int n) {
  struct Node *curr, *prev;
  int count;

  curr = head;
  prev = NULL;
  count = 0;

  while(n > 1) {
    count++;
    if(count == k) {
      printf("Person %d evicted\n", curr->id);
      prev->next = curr->next;
      free(curr);
      curr = prev->next;
      count = 0;
      n--;
    } else {
      prev = curr;
      curr = curr->next;
    }
  }

  printf("Winner is Person %d\n", curr->id);
}

int main() {
  int n, k;
  printf("Enter number of persons: ");
  scanf("%d", &n);

  printf("Enter number to skip: ");
  scanf("%d", &k);

  struct Node* head = createCircle(n);

  playGame(head, k, n);

  return 0;
}