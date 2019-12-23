#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "queue_ll.h"

/* Local Functions */
static int is_full(Queue *queue) {
  int count = queue_get_length(queue);
  if(count >= MAX_QUEUE) {
    return 1;
  }
  else {
    return 0;
  }
}

static int is_empty(Queue *queue) {
  if(queue == NULL || queue->front == NULL) {
    return 1;
  }
  else {
    return 0;
  }
}

static Node *create_node(void *elem) {
  Node *new_node = malloc(sizeof(Node));
  if(new_node != NULL) {
    new_node->elem = elem;
    new_node->next = NULL;
  }
  return new_node;
}

/* Initialize a new Linked List Based Queue */
Queue *queue_initialize() {
  Queue *new_queue = malloc(sizeof(Queue));
  if(new_queue != NULL) {
    new_queue->count = 0;
    new_queue->front = NULL;
    new_queue->rear = NULL;
  }

  return new_queue;
}

/* Adds a new element into the queue, return 0 if full */
int queue_enqueue(Queue *queue, void *elem) {
  Node *node = NULL;
  if(queue == NULL || is_full(queue)) {
    return 0;
  }

  node = create_node(elem);
  if(node != NULL) {
    if(is_empty(queue)) {
      queue->front = node;
      queue->rear = node;
      queue->count = 1;
      return 1;
    }
    else {
      queue->rear->next = node;
      queue->rear = node;
      queue->count++;
      return 1; // Node inserted
    }
  }
  else {
    return 0; // Failed to create node
  }
}

/* Dequeues an element and returns it */
void *queue_dequeue(Queue *queue) {
  void *elem = NULL;
  
  if(queue == NULL || is_empty(queue)) {
    return NULL;
  }
  else {
    elem = queue->front->elem;
    queue->front = queue->front->next;
    queue->count--;
    if(queue->front == NULL) {
      queue->rear = NULL;
    }
    return elem;
  }
}

/* Returns the first element in the queue (FRONT) */
void *queue_peek(Queue *queue) {
  if(queue == NULL || is_empty(queue)) {
    return NULL;
  }
  else {  
    return queue->front->elem;
  }
}

/* Prints the queue using the element print function */
void queue_print(Queue *queue, void (*elem_print)(void *elem)) {
  Node *walker = NULL;
  if(queue == NULL || elem_print == NULL) {
    printf("Queue Not Initialized\n");
    return;
  }

  if(is_empty(queue)) {
    printf("Queue: [ 0 customers] Empty\n");
  }
  else {
    printf("Queue: [%2d customers]", queue_get_length(queue));
    for(walker = queue->front; walker != NULL; walker = walker->next) {
      (*elem_print)(walker->elem);
    }
    printf("\n");
  }
}

/* Returns the length of the queue */
int queue_get_length(Queue *queue) {
  if(queue != NULL) {
    return queue->count;
  }
  else {
    return 0;
  }
}

/* Destroys the queue */
void queue_destroy(Queue *queue) {
  Node *walker = NULL;
  Node *reaper = NULL;

  if(queue == NULL) {
    return;
  }
  else {
    walker = queue->front;
    while(walker != NULL) {
      reaper = walker;
      walker = walker->next;
      free(reaper);
      reaper = NULL;
    }

    free(queue);
    queue = NULL;
  }
  return;
}
