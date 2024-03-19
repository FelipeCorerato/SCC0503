#ifndef SCC0503_QUEUE_H
#define SCC0503_QUEUE_H

typedef struct Queue {
    int size;
    int lastIndex;
    int* array;
} Queue;

void initializeQueue(Queue* queue, int size);
void enqueue(Queue* queue, int value);
int dequeue(Queue* queue);
int isQueueEmpty(Queue* queue);
void destroyQueue(Queue* queue);

#endif
