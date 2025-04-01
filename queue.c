#include "queue.h"

#define MAX_QUEUE 100
struct _Queue
{
    void *data[MAX_QUEUE];
    void **front;
    void **rear;
};

Queue *queue_new()
{
    Queue *new_queue = NULL;
    int i;

    new_queue = (Queue *)calloc(1, sizeof(Queue));
    if (!new_queue)
    {
        return NULL;
    }

    for (i = 0; i < MAX_QUEUE; i++)
    {
        new_queue->data[i] = NULL;
    }
    new_queue->front = &(new_queue->data[0]);
    new_queue->rear = &(new_queue->data[0]);

    return new_queue;
}

void queue_free(Queue *q) { free(q); }

Bool queue_isEmpty(const Queue *q)
{
    if (!q)
    {
        return TRUE;
    }

    if (q->front == q->rear)
    {
        return TRUE;
    }
    return FALSE;
}

Status queue_push(Queue *q, void *ele)
{
    if (!q || !ele)
    {
        return ERROR;
    }

    /*Comprobacion de error si esta la cola llena*/
    if ((q->front - q->data) == (q->rear - q->data + sizeof(void *)) % MAX_QUEUE)
    {
        return ERROR;
    }

    *(q->rear) = (void *)ele;
    q->rear = (q->rear - q->data + 1) % MAX_QUEUE + q->data;

    return OK;
}

void *queue_pop(Queue *q)
{
    void *e = NULL;

    if (!q || queue_isEmpty(q) == TRUE)
    {
        return NULL;
    }

    e = *(q->front);
    *(q->front) = NULL;
    q->front = (q->front - q->data + 1) % MAX_QUEUE + q->data;

    return e;
}

void *queue_getFront(const Queue *q)
{
    if (!q || queue_isEmpty(q) == TRUE)
    {
        return NULL;
    }

    return *(q->front);
}

void *queue_getBack(const Queue *q)
{
    void **e = NULL;

    if (!q || queue_isEmpty(q) == TRUE)
    {
        return NULL;
    }

    if (q->rear == q->data)
    {
        e = ((Queue *)q)->data + MAX_QUEUE - 1;
    }
    else
    {
        e = q->rear - 1;
    }
    return *e;
}

size_t queue_size(const Queue *q)
{
    if (!q)
    {
        return 0;
    }

    return ((q->rear - q->front - sizeof(void *) + MAX_QUEUE) % MAX_QUEUE);
}

int queue_print(FILE *fp, const Queue *q, p_queue_ele_print f)
{
    void *e = NULL;
    size_t size = queue_size(q);
    Queue *aux = NULL;
    int i, count = 0;

    if (!fp || !q || !f)
    {
        return -1;
    }

    aux = queue_new();
    if (!aux)
    {
        return -1;
    }

    for (i = 0; i < size; i++)
    {
        e = queue_pop((Queue*)q);
        if (!e||queue_push(aux, e) == ERROR)
        {
            while(queue_isEmpty(aux)==FALSE){
                e = queue_pop(aux);
                queue_push((Queue*)q, e);
            }
            queue_free(aux);
            return -1;
        }

        count += f(fp, e);
        count += fprintf(fp, "\n");
    }

    /*Se restaura la cola original*/
    while(queue_isEmpty(aux)==FALSE){
        e = queue_pop(aux);
        queue_push((Queue*)q, e);
    }
    queue_free(aux);

    return count;
}