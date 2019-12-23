#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "queue_array.h"

/* Local Functions */
static int is_full(Queue *queue) {
  if(queue == NULL) {
    return -1;
  }
  /* If rear is one behind front, we're calling this full */
  if((queue->rear + 1) % MAX_QUEUE == queue->front) {
    return 1;
  } 
  else {
    return 0;
  }
}

static int is_empty(Queue *queue) {
  if(queue == NULL) {
    return -1;
  }
  /* If front equals rear, we're empty */
  if(queue->rear == queue->front) {
    return 1;
  } 
  else {
    return 0;
  }
}

/* Initialize a new Array Based Queue */
Queue *queue_initialize() {
  Queue *queue = malloc(sizeof(Queue));
  if(queue != NULL) {
    queue->front = 0; 
    queue->rear = 0;
  }
  return queue;
}

/* Adds a new element into the queue, return 0 if full */
int queue_enqueue(Queue *queue, void *elem) {
  if(queue == NULL) {
    return -1;
  }

  if(!is_full(queue)) {
    queue->elems[queue->rear] = elem;
    queue->rear = (queue->rear + 1) % MAX_QUEUE;
    return 1;
  }
  return 0;
}

/* Dequeues an element and returns it */
void *queue_dequeue(Queue *queue) {
  void *elem = NULL;
  
  if(queue == NULL) {
    return NULL;
  }

  if(!is_empty(queue)) {
    elem = queue->elems[queue->front];
    queue->front = (queue->front + 1) % MAX_QUEUE;
  }
  return elem;
}

/* Returns the first element in the queue (FRONT) */
void *queue_peek(Queue *queue) {
  if(queue == NULL) {
    return NULL;
  }
  
  if(!is_empty(queue)) {
    return queue->elems[queue->front];
  }
  else {
    return NULL;
  }
}

/* Prints the queue using the element print function */
void queue_print(Queue *queue, void (*elem_print)(void *elem)) {
  if(queue == NULL || elem_print == NULL) {
    printf("Queue Not Initialized\n");
    return;
  }

  if(is_empty(queue)) {
    printf("Queue: [ 0 customers] Empty\n");
  }
  else {
    printf("Queue: [%2d customers] (%d,%d)", queue_get_length(queue), queue->front, queue->rear);
    int index = queue->front;
    while(index != queue->rear) {
      (*elem_print)(queue->elems[index]);
      index = (index + 1) % MAX_QUEUE;
      if(index != queue->rear) {
        printf(", ");
      } 
    }
    printf("\n");
  }
}

/* Returns the length of the queue */
int queue_get_length(Queue *queue) {
  if(queue != NULL) {
    if(!is_empty(queue)) {
      if(queue->rear < queue->front) {
        return queue->rear + MAX_QUEUE - queue->front;
      }
      else {
        return queue->rear - queue->front;
      }
    }
    else {
      return 0;
    }
  }
  else {
    return 0;
  }
}

/* Destroys the queue */
void queue_destroy(Queue *queue) {
  free(queue);
  queue = NULL;
  return;
}
