#include <stdio.h>
#include <stdlib.h>
#include "cola.h"

typedef struct Node {
    struct Node *next;
    int data;
}node_t;

struct Queue{
    node_t *top;
    node_t *bottom;
    int size;
};

node_t *createNode(int data) {
    node_t *node = (node_t *) calloc (1, sizeof(node_t));
    node->data = data;

    return node;
}

int removeNode(node_t *node) {
    node->next = NULL;
    free(node);

    return (node == NULL);
}

queue_t *createQueue() {
    queue_t *queue = (queue_t *)calloc(1, sizeof(queue_t));

    return queue;
}

int removeQueue(queue_t *queue) {
    node_t *ptr = queue->top;
    node_t *aux;

    while (ptr->next != NULL) {
        aux = ptr;
        ptr = ptr->next;

        removeNode(aux);
        queue->size--;
    }

    free(queue);

    return (queue == NULL);
}

int peek(queue_t *queue) {
    if (queue != NULL)
        return queue->top->data;
    else
        return -1;
}

int isEmpty(queue_t *queue) {
    return (queue->top == NULL);
}

void enqueue(int data, queue_t *queue) {
    if (queue != NULL) {
        node_t *new = createNode(data);

        if (queue->top == NULL) {
            queue->bottom = new;
            queue->top = new;

        } else {
            node_t *ptr = queue->top;
            while (ptr != queue->bottom) {
                ptr = ptr->next;
            }
            ptr->next = new;
            new->next = NULL;
            queue->bottom = new;
        }

        queue->size++;
    }
}

int dequeue(queue_t *queue) {
    if (queue != NULL && queue->top != NULL) {
        int data;
        node_t *aux = queue->top;
        queue->top = aux->next;
        data = aux->data;
        removeNode(aux);

        queue->size--;
        return data;
    } else {
        return -1;
    }
}

int getQueueSize(queue_t *queue) {
    return queue->size;
}
