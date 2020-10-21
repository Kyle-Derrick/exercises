#include <stdlib.h>
#include <string.h>
#include "queue.h"

const size_t _STACK_TYPE_SIZE_ = sizeof(Queue);
const size_t _STACK_NODE_TYPE_SIZE_ = sizeof(_QueueNode_);

Queue* new_queue(size_t type)
{
    Queue *queue = malloc(_STACK_TYPE_SIZE_);
    queue->size = 0;
    queue->type = type;
    queue->first = NULL;
    queue->last = NULL;

    return queue;
}

Queue* queue_add(Queue *qe, void *value)
{
    _QueueNode_ *node = malloc(_STACK_NODE_TYPE_SIZE_);
    node->value = value;
    node->next = NULL;
    switch (qe->size)
    {
    case 0:
        qe->first = node;
        qe->last = node;
        break;
    
    default:
        qe->last->next = node;
        qe->last = node;
        break;
    }
    qe->size++;

    return qe;
}

Queue* queue_addn(Queue *qe, void *value)
{
    void *tmp = malloc(qe->type);
    memcpy(tmp, value, qe->type);
    return queue_add(qe, tmp);
}

Queue* queue_insert(Queue *qe, size_t index, void *value)
{
    if (index > qe->size-1)
    {
        return queue_add(qe, value);
    }else if (index < 0)
    {
        index = 0;
    }
    
    _QueueNode_ *node = malloc(_STACK_NODE_TYPE_SIZE_);
    node->value = value;
    node->next = NULL;

    switch (qe->size)
    {
    case 0:
        qe->first = node;
        qe->last = node;
        break;
    
    default:
        _QueueNode_ *tmplast = NULL;
        _QueueNode_ *tmp = qe->first;
        while (index--)
        {
            tmplast = tmp;
            tmp = tmp->next;
        }

        if (tmplast)
        {
            tmplast->next = node;
        }else
        {
            qe->first = node;
        }
        
        node->next = tmp;
        break;
    }
    qe->size++;

    return qe;
}

Queue* queue_insertn(Queue *qe, size_t index, void *value)
{
    if (index > qe->size-1)
    {
        return queue_addn(qe, value);
    }
    void *tmp = malloc(qe->type);
    memcpy(tmp, value, qe->type);
    return queue_insert(qe, index, tmp);
}

void* queue_del(Queue *qe, size_t index)
{
    if (index > qe->size-1)
    {
        index = qe->size - 1;
    }else if (index < 0)
    {
        index = 0;
    }

    switch (qe->size)
    {
    case 0:
        return NULL;
    
    default:
        _QueueNode_ *tmplast = NULL;
        _QueueNode_ *tmp = qe->first;
        while (index--)
        {
            tmplast = tmp;
            tmp = tmp->next;
        }

        if (tmplast)
        {
            tmplast->next = tmp->next;
        }else
        {
            qe->first = tmp->next;
        }
        
        free(tmp);
        qe->size--;
        return tmp;
    }
}

void queue_dela(Queue *qe, size_t index)
{
    void *tmp = queue_del(qe, index);
    if (tmp)
    {
        free(tmp);
    }
}

Queue* queue_update(Queue *qe, size_t index, void *value)
{
    if (index > qe->size-1 || index < 0 || qe->size == 0)
    {
        return qe;
    }

    _QueueNode_ *tmp = qe->first;
    while (index--)
    {
        tmp = tmp->next;
    }

    tmp->value = value;

    return qe;
}

Queue* queue_updaten(Queue *qe, size_t index, void *value)
{
    if (index > qe->size-1 || index < 0 || qe->size == 0)
    {
        return qe;
    }
    void *tmp = malloc(qe->type);
    memcpy(tmp, value, qe->type);
    return queue_update(qe, index, tmp);
}

//待续
Queue* queue_indexOf(Queue *qe, void *value)
{
    if (index > qe->size-1 || index < 0 || qe->size == 0)
    {
        return qe;
    }

    _QueueNode_ *tmp = qe->first;
    while (index--)
    {
        tmp = tmp->next;
    }

    tmp->value = value;

    return qe;
}

Queue* queue_updaten(Queue *qe, size_t index, void *value)
{
    if (index > qe->size-1 || index < 0 || qe->size == 0)
    {
        return qe;
    }
    void *tmp = malloc(qe->type);
    memcpy(tmp, value, qe->type);
    return queue_update(qe, index, tmp);
}

void* queue_pop(Queue *qe)
{
    if (!qe->last)
    {
        return NULL;
    }
    
    _QueueNode_ *last = qe->last;
    void *value = last->value;
    qe->last = last->next;
    free(last);
    qe->size--;

    return value;
}

int queue_popp(Queue *qe, void *value)
{
    void *tmp;
    if (!(tmp = queue_pop(qe)))
    {
        return -1;
    }
    memcpy(value, tmp, qe->type);
    free(tmp);

    return 0;
}

size_t queue_size(Queue *qe)
{
    if (!qe->last)
    {
        return 0;
    }
    _QueueNode_ *tmp = qe->last;
    size_t size = 0;
    do
    {
        size++;
    }while (tmp = tmp->next);
    
    return qe->size;
}

void queue_destory(Queue *qe)
{
    while (queue_pop(qe));
    free(qe);
}

void queue_destorya(Queue *qe)
{
    void *tmp = queue_pop(qe);
    while (tmp)
    {
        free(tmp);
        tmp = queue_pop(qe);
    }
    free(qe);
}