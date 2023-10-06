#include <stdio.h>
#include <stdlib.h>
#include<time.h>


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

int dequeueInteger(queue q, int *dp) {
    if (q->front == q->rear) {
        return 0;
    }
    *dp = q->data[q->front];
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

int generateRandomVal() {
    return rand() % 9 + 1;
}

int main() {
    srand(time(NULL));

    int N;
    printf("Enter the size of the queue: ");
    scanf("%d", &N);

    queue myQueue = createIntegerQueue(N);
    if (myQueue == NULL) {
        printf("Queue creation failed.\n");
        return 1;
    }


    int input;
    printf("Enter positive integers to enqueue in the queue (Enter -1 to end):\n");
    while (1) {
        scanf("%d", &input);
        if (input == -1) {
            break;
        }
        enqueueInteger(myQueue, input);
    }


    while (!isIntegerQueueEmpty(myQueue)) {
        int qElem;
        if (dequeueInteger(myQueue, &qElem)) {
            if (qElem > 0) {
                int rVal = generateRandomVal();
                qElem -= rVal;
                if (qElem > 0) {
                    printf("element %d, rValue = %d, Updated element = %d\n",
                           qElem + rVal, rVal, qElem);
                    enqueueInteger(myQueue, qElem);
                }
            }
        }
    }


    freeIntegerQueue(myQueue);

    return 0;
}