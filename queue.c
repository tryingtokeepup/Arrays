#include <stdlib.h>
#include <stdio.h>

// The queue struct
typedef struct Queue
{
    unsigned int capacity;
    unsigned int head;
    unsigned int tail;
    unsigned int count;
    int *data;
} Queue;

// Create a queue with the given capacity
Queue *createQueue(unsigned capacity)
{
    Queue *queue = malloc(sizeof(Queue));
    queue->capacity = capacity;
    queue->head = 0;
    queue->tail = 0;
    queue->count = 0;
    queue->data = malloc(capacity * sizeof(int));

    return queue;
}

int isQFull(Queue *queue)
{
    return queue->count == queue->capacity;
}

int isQEmpty(Queue *queue)
{
    return queue->count == 0;
}

// Add and item to the queue
void enqueue(Queue *queue, int item)
{
    if (!isQFull(queue))
    {
        queue->data[queue->tail] = item;
        queue->tail = (queue->tail + 1) % queue->capacity;
        queue->count++;
    }
}

// Remove the queue element that was least-recently added
int dequeue(Queue *queue)
{
    if (!isQEmpty(queue))
    {
        int head = queue->head;
        queue->head = (queue->head + 1) % queue->capacity;
        queue->count--;
        return queue->data[head];
    }

    return -1;
}

// Program to test above functions
int main()
{
    Queue *queue = createQueue(100);

    enqueue(queue, 10);
    enqueue(queue, 20);
    enqueue(queue, 30);

    printf("%d dequeued from queue\n", dequeue(queue));
    printf("%d dequeued from queue\n", dequeue(queue));
    printf("%d dequeued from queue\n", dequeue(queue));

    return 0;
}