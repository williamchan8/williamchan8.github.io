#include "queue.hpp"
#include <iostream>
 
// Function to create a queue of given capacity
// It initializes size of queue as 0
Queue::Queue(int* initial, int capacity) {
  Queue* q = (Queue*)malloc(sizeof(Queue));
  buffer = (int *)(malloc(capacity * sizeof(int)));
  length = 0;
  if (initial != NULL) {
    memcpy(buffer, initial, capacity * sizeof(int));
    length = capacity;
  }
  cap = capacity;
  front = 0;
  rear = 0;
}

Queue::~Queue(){
    free(buffer);
}

void Queue::push(int value) {
  buffer[rear] = value;
  rear = (rear + 1) % length;
  ++length;
}

int Queue::pop() {
  int retval = buffer[front];
  front = (front + 1) % length;
  --length;
  return retval;
}

int Queue::size() {
  return length;
}

void Queue::print() {
  printf("\n( ");
  for (int i = 0; i < length; ++i) {
    printf("%d ", buffer[(i + front) % length]);
  }
  printf(")\n\n");
}