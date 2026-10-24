#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int customerNumber;
    struct Node *next;
} Node;

typedef struct Queue {
    Node *front;
    Node *rear;
} Queue;


void initQueue(Queue *q) {
    q->front = NULL;
    q->rear = NULL;
}

int isEmpty(Queue q) {
    return q.front == NULL;
}

void enqueue(Queue *q, int number) {
    Node *n = (Node *)malloc(sizeof(Node));
    if (n == NULL) {
        printf("Memory allocation failed.\n");
        exit(1);
    }
    n->customerNumber = number;
    n->next = NULL;

    if (q->rear == NULL) {
        q->front = n;
        q->rear = n;
    } else {
        q->rear->next = n;
        q->rear = n;
    }
}

int dequeue(Queue *q) {
    if (isEmpty(*q)) {
        printf("Error: queue is empty.\n");
        return -1;
    }
    Node *tmp = q->front;
    int value = tmp->customerNumber;
    q->front = tmp->next;
    if (q->front == NULL)
        q->rear = NULL;
    free(tmp);
    return value;
}

int peek(Queue q) {
    if (isEmpty(q)) {
        printf("Error: queue is empty.\n");
        return -1;
    }
    return q.front->customerNumber;
}


void customerArrives(Queue *q, int token) {
    enqueue(q, token);
    printf("Customer %d arrived and got a token.\n", token);
}

void serveCustomer(Queue *q) {
    if (isEmpty(*q)) {
        printf("Queue is empty.\n");
        return;
    }
    printf("Customer %d is being served.\n", dequeue(q));
}

int main(void) {
    Queue q;
    initQueue(&q);

    customerArrives(&q, 101);
    customerArrives(&q, 102);
    serveCustomer(&q);
    customerArrives(&q, 103);
    serveCustomer(&q);
    serveCustomer(&q);

    if (isEmpty(q))
        printf("Queue is empty.\n");

    return 0;
}
