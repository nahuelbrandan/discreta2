#ifndef BRANDAN_COSTAMAGNA_DIARTE_COLA_H_
#define BRANDAN_COSTAMAGNA_DIARTE_COLA_H_

typedef struct Queue queue_t;

queue_t *createQueue();
int removeQueue(queue_t *);

// retorna valor de la cabeza, o -1 si esta vacia.
int peek(queue_t *);
int isEmpty(queue_t *);


// la cola tiene que ser distinto de NULL.
void enqueue(int, queue_t *);

// retorna -1 si la cola esta vacia.
int dequeue(queue_t *);

int getQueueSize(queue_t *);

#endif  // BRANDAN_COSTAMAGNA_DIARTE_COLA_H_
