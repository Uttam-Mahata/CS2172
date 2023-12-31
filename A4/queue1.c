#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *data;
    int front;
    int rear;
    int size;
} *queue;

queue createIntegerQueue(int queueSize) {
    queue q = (queue)malloc(sizeof(queue));
    if (q == NULL) {
        return NULL;
    }
    q->data = (int *)malloc(queueSize * sizeof(int));
    if (q->data == NULL) {
        free(q);
        return NULL;
    }
    q->front = 0;
    q->rear = 0;
    q->size = queueSize;
    return q;
}

int enqueueInteger(queue q, int d) {
    if ((q->rear + 1) % q->size == q->front) {
        return 0;
    }
    q->data[q->rear] = d;
    q->rear = (q->rear + 1) % q->size;
    return 1;
}

int dequeueInteger(queue q, int *dptr) {
    if (q->front == q->rear) {
        return 0;
    }
    *dptr = q->data[q->front];
    q->front = (q->front + 1) % q->size;
    return 1;
}

int freeIntegerQueue(queue q) {
    if (q == NULL) {
        return 0;
    }
    free(q->data);
    free(q);
    return 1;
}

int isIntegerQueueFull(queue q) {
    return ((q->rear + 1) % q->size == q->front);
}

int isIntegerQueueEmpty(queue q) {
    return (q->front == q->rear);
}

int main() {
int arrSize;
int elem[arrSize];
printf("Enter the number of  integers to be enqueued: \n");
scanf("%d",&arrSize);

    queue q = createIntegerQueue(arrSize);
    if (q == NULL) {
        printf("Queue creation failed.\n");
        return 1;
    }

    printf("Is queue empty: %s\n", isIntegerQueueEmpty(q) ? "Yes" : "No");
    printf("Is queue full: %s\n", isIntegerQueueFull(q) ? "Yes" : "No");

    /*enqueueInteger(q, 11);
    enqueueInteger(q, 12);
    enqueueInteger(q, 10);
    enqueueInteger(q, 20);*/

    printf("Enter the value integers to be enqueued:\n");
    for(int i=0;i<arrSize;i++) {
    scanf("%d",&elem[i]);

}
 for(int i=0;i<arrSize;i++) {
    enqueueInteger(q,elem[i]);

}






    int val;
    if (dequeueInteger(q, &val)) {
        printf("Dequeued: %d\n", val);
    }

    printf("Is queue empty: %s\n", isIntegerQueueEmpty(q) ? "Yes" : "No");
    printf("Is queue full: %s\n", isIntegerQueueFull(q) ? "Yes" : "No");

    freeIntegerQueue(q);
    return 0;
}