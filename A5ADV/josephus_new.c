#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct Node {
    int id;
    struct Node* next;
};

struct Node* createCircle(int n) {
    struct Node* head = NULL;
    struct Node* prev = NULL;

    for (int i = 1; i <= n; i++) {
        struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
        if (newNode == NULL) {
            fprintf(stderr, "Memory allocation error\n");
            exit(1);
        }
        newNode->id = i;
        newNode->next = NULL;

        if (head == NULL) {
            head = newNode;
        } else {
            prev->next = newNode;
        }
        prev = newNode;
    }

    if (head != NULL) {
        prev->next = head;
    }

    return head;
}

int f1(int x) {
    return x * x - 2 * x + 1;
}

int f2(int x) {
    return x * x * x - x * x + x;
}

void playGame(struct Node* head, int n) {
    srand(time(NULL));

    struct Node* curr = head;
    struct Node* prev = NULL;

    while (n > 1) {
        int rand_fun = rand() % 2 + 1;
        int x = rand() % 10 + 1;
        int skip;

        if (rand_fun == 1) {
            skip = f1(x);
        } else {
            skip = f2(x);
        }

        if (n % 2 == 0) {
            skip = skip % n;
        }

        for (int i = 0; i < skip; i++) {
            prev = curr;
            curr = curr->next;
        }

        printf("Person %d evicted\n", curr->id);

        prev->next = curr->next;
        free(curr);

        curr = prev->next;
        n--;
    }

    printf("Winner is Person %d\n", curr->id);
}

int main() {
    int n;

    printf("Enter the number of persons: ");
    scanf("%d", &n);

    if (n <= 0) {
        printf("Invalid input. Number of persons must be greater than 0.\n");
        return 1;
    }

    struct Node* head = createCircle(n);

    playGame(head, n);

    return 0;
}
