#include <stdio.h>
#include <stdlib.h>

typedef enum
{
    ERROR,
    OK
} Bool;
typedef struct
{
    char *data;
    int capacity;
    int front, rear;
} Queue;

Queue *new_queue(int capacity)
{
    Queue *q = NULL;

    q = (Queue *)calloc(1, sizeof(Queue));

    if (!q)
    {
        return NULL;
    }

    q->data = (char *)calloc(capacity + 1, sizeof(char));
    q->capacity = capacity;
    q->front = q->rear = 0; /*Al ser circular, no importa con qué valor inicialicemos*/
    /*También se podría iniciar rear a -1 y front a 0, luego al hacer push tendríamos que mover rear primero
    y luego guardar el dato*/

    return q;
}
Bool empty(Queue *q)
{
    if (!q)
    {
        return ERROR;
    }

    return q->front == q->rear;
}

Bool full(Queue *q)
{
    if (!q)
    {
        return ERROR;
    }

    return q->front == ((q->rear + 1) % (q->capacity)); /*capacity+1*/
}

char pop(Queue *q)
{
    char x;

    if (!q)
    {
        return '\0';
    }

    if (empty(q))
    {
        return '\0';
    }

    x = q->data[q->front];
    q->front = (q->front + 1) % q->capacity; /*capacity+1*/
    return q->data[q->front];
}

void push(Queue *q, char c)
{
    if (!q)
    {
        return '\0';
    }

    if (full(q))
    {
        return '\0';
    }

    q->data[q->rear] = c;

    q->rear = (q->rear + 1) % (q->capacity); /*capacity+1*/
}

char front(Queue *q)
{
    if (!q)
    {
        return '\0';
    }

    return q->data[q->front];
}

char rear(Queue *q)
{
    if (!q)
    {
        return '\0';
    }

    return q->data[(q->rear - 1 + q->capacity) % q->capacity];
}