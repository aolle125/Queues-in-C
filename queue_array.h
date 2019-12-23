#ifndef QUEUE_ARRAY_H
#define QUEUE_ARRAY_H

#define MAX_QUEUE 10

typedef struct queue {
  void *elems[MAX_QUEUE];
  int front;
  int rear;
} Queue;

/* Initialize a new Queue */
Queue *queue_initialize();

/* Adds a new element into the queue */
int queue_enqueue(Queue *queue, void *elem);

/* Dequeues an element and returns it */
void *queue_dequeue(Queue *queue);

/* Returns the first element in the queue (FRONT) */
void *queue_peek(Queue *queue);

/* Prints the queue using the element print function */
void queue_print(Queue *queue, void (*elem_print)(void *elem));

/* Returns the length of the queue */
int queue_get_length(Queue *queue);

/* Destroys the queue */
void queue_destroy(Queue *queue);

#endif
