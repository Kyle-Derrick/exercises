#include <stdlib.h>
#include <string.h>
#include "tools.h"
#include "queue.h"

const size_t _QUEUE_TYPE_SIZE_ = sizeof(Queue);
const size_t _QUEUE_NODE_TYPE_SIZE_ = sizeof(_QueueNode_);

_QueueNode_ *_clone_queue_node_(void *value, size_t size, int flags);
_QueueNode_ *_get_queue_node_(Queue *qe, size_t index);
_QueueNode_* _queue_update_with_lastnode_(Queue *qe, _QueueNode_ *lastnode, void *value, int flags);
Queue *string_to_queue(char *str);
Queue *string_to_queue_l(char *str, size_t len);
Queue* new_queue(size_t type);
Queue* queue_add(Queue *qe, void *value, int flags);
Queue *queue_clone_all(Queue *qe, int flags);
Queue *queue_clone(Queue *qe, size_t start, size_t end, int flags);
int queue_cmp(Queue *qe, Queue *qe2);
int queue_cmpf(Queue *qe, Queue *qe2, int fun(const void*, const void*, size_t));
Queue* queue_concat_arr(Queue *qe, void *value, size_t len, int flags);
Queue* queue_concat(Queue *q1, Queue *q2, int flags);
void* queue_del(Queue *qe, size_t index, int flags);
void queue_destory(Queue *qe, int flags);
void *queue_each(Queue *qe, void *arg, void *fun(Queue*,_QueueNode_*,_QueueNode_*,_QueueNode_**,size_t,void*,void*));
void* queue_get(Queue *qe, size_t index);
void queue_getn(Queue *qe, size_t index, void *value);
ssize_t queue_indexOf(Queue *qe, void *value);
ssize_t queue_indexOff(Queue *qe, void *value, int fun(const void*, const void*, size_t));
Queue* queue_insert_all_arr(Queue *qe, size_t index, void *value, size_t len, int flags);
Queue* queue_insert_all(Queue *q1, Queue *q2, size_t index, int flags);
Queue* queue_insert(Queue *qe, size_t index, void *value, int flags);
void* queue_shift(Queue *qe);
int queue_shiftp(Queue *qe, void *value);
size_t queue_size(Queue *qe);
void* queue_to_array_all(Queue *qe, int flags);
void* queue_to_array(Queue *qe, size_t start, size_t end, int flags);
Queue *queue_update_arr_diy(Queue *qe, size_t start, size_t end, void *value, size_t len, int flags);
Queue *queue_update_diy(Queue *q1, Queue *q2, size_t start, size_t end, int flags);
Queue* queue_update(Queue *qe, size_t index, void *value, int flags);

Queue *string_to_queue(char *str)
{
    return string_to_queue_l(str, strlen(str));
}

Queue *string_to_queue_l(char *str, size_t len)
{
    Queue *q = new_queue(sizeof(char));
    queue_concat_arr(q, str, len, CREATE_NEW_VALUE);
    return q;
}

Queue* new_queue(size_t type)
{
    Queue *queue = malloc(_QUEUE_TYPE_SIZE_);
    queue->size = 0;
    queue->type = type;
    queue->first = NULL;
    queue->last = NULL;

    return queue;
}

Queue* queue_add(Queue *qe, void *value, int flags)
{
    _QueueNode_ *node = _clone_queue_node_(value, qe->type, flags);
    if (qe->first)
    {
        qe->last->next = node;
    }else
    {
        qe->first = node;
    }
    qe->last = node;
    qe->size++;

    return qe;
}

Queue* queue_insert(Queue *qe, size_t index, void *value, int flags)
{
    return queue_insert_all_arr(qe, index, value, 1, flags);
}

Queue* queue_insert_all_arr(Queue *qe, size_t index, void *value, size_t len, int flags)
{
    int f = flags & CREATE_NEW_VALUE + INSERT_NODE;
    return queue_update_arr_diy(qe, index, 0, value, len, f);
}

Queue* queue_insert_all(Queue *q1, Queue *q2, size_t index, int flags)
{
    int f = flags - flags & UPDATE_NODE + INSERT_NODE;
    return queue_update_diy(q1, q2, index, 0, f);
}

Queue* queue_concat_arr(Queue *qe, void *value, size_t len, int flags)
{
    for (size_t i = 0; i < len; i++)
    {
        queue_add(qe, 
                value+i*qe->type, flags);
    }
    return qe;
}

Queue* queue_concat(Queue *q1, Queue *q2, int flags)
{
    if (q2->first)
    {
        if (flags & CLONE_NEW_QUEUE)
        {
            q2 = queue_clone_all(q2, flags);
        }
    }else
    {
        return q1;
    }
    
    if (!q1->first)
    {
        q1->first = q2->first;
        q1->last = q2->last;
    }else
    {
        q1->last->next = q2->first;
    }
    
    q1->size += q2->size;

    if (flags & CLONE_NEW_QUEUE)
    {
        q2->first = NULL;
        queue_destory(q2, NONE_FLAGS);
    }
    return q1;
}

void* queue_del(Queue *qe, size_t index, int flags)
{
    int f = DELETE_NODE + flags & DELETE_OLD_VALUE_CREATE_NEW;
    return queue_update_arr_diy(qe, index, 0, NULL, 0, f);
}

Queue* queue_update(Queue *qe, size_t index, void *value, int flags)
{
    int f = UPDATE_NODE + flags & DELETE_OLD_VALUE_CREATE_NEW;
    return queue_update_arr_diy(qe, index, 0, value, 1, f);
}

ssize_t queue_indexOf(Queue *qe, void *value)
{
    return queue_indexOff(qe, value, memcmp);
}

ssize_t queue_indexOff(Queue *qe, void *value, int fun(const void*, const void*, size_t))
{
    if (qe->size == 0)
    {
        return -1;
    }

    size_t index = 0;
    _QueueNode_ *tmp = qe->first;
    do
    {
        if (!fun(tmp->value, value, qe->type))
        {
            return index;
        }
        index++;
    }while ((tmp = tmp->next));

    return -1;
}

int queue_cmp(Queue *qe, Queue *qe2)
{
    return queue_cmpf(qe, qe2, memcmp);
}

int queue_cmpf(Queue *qe, Queue *qe2, int fun(const void*, const void*, size_t))
{
    if (qe->size != qe2->size)
    {
        return -1;
    }
    if (qe->size == 0)
    {
        return 0;
    }

    _QueueNode_ *tmp = qe->first;
    _QueueNode_ *tmp2 = qe2->first;
    do
    {
        if (fun(tmp->value, tmp2->value, qe->type))
        {
            return -1;
        }
    }while ((tmp = tmp->next) && (tmp2 = tmp2->next));

    return 0;
}

void* queue_get(Queue *qe, size_t index)
{
    if (qe->size == 0)
    {
        return NULL;
    }
    if (index == qe->size - 1)
    {
        return qe->last->value;
    }
    

    _QueueNode_ *tmp = qe->first;
    do
    {
        if (!index--)
        {
            return tmp->value;
        }
    }while ((tmp = tmp->next));

    return NULL;
}

void queue_getn(Queue *qe, size_t index, void *value)
{
    void *v = queue_get(qe, index);
    if (v)
    {
        memcpy(value, v, qe->type);
    }
    return;
}

void* queue_shift(Queue *qe)
{
    if (!qe->first)
    {
        return NULL;
    }
    
    _QueueNode_ *first = qe->first;
    void *value = first->value;
    qe->first = first->next;
    if (first == qe->last)
    {
        qe->last = first->next;
    }
    
    free(first);
    qe->size--;

    return value;
}

int queue_shiftp(Queue *qe, void *value)
{
    void *tmp;
    if (!(tmp = queue_shift(qe)))
    {
        return -1;
    }
    memcpy(value, tmp, qe->type);
    free(tmp);

    return 0;
}

void* queue_to_array(Queue *qe, size_t start, size_t end, int flags)
{
    if (start >= qe->size || start > end || (start == end && end != 0))
    {
        return NULL;
    }

    size_t step = end - start;
    if (!end)
    {
        step = qe->size - start;
    }
    
    _QueueNode_ *tmp = qe->first;
    size_t type = 0;
    if (flags & CREATE_NEW_VALUE)
    {
        type = qe->type;
    }else
    {
        type = sizeof(void*);
    }
    
    size_t i = 0;
    void *arr = malloc(step * type);
    do
    {
        if (i >= start)
        {
            void *t = arr+i*type;
            if (flags & CREATE_NEW_VALUE)
            {
                memcpy(t, tmp->value, type);
            }else
            {
                memcpy(t, &(tmp->value), type);
            }
        }
        i++;
    } while ((tmp = tmp->next) && i < step);
    return arr;
}

void* queue_to_array_all(Queue *qe, int flags)
{
    return queue_to_array(qe, 0, 0, flags);
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

void queue_destory(Queue *qe, int flags)
{
    void *tmp = NULL;
    while (tmp = queue_shift(qe))
    {
        if (flags & DELETE_WITH_VALUE)
        {
            free(tmp);
        }
    }
    free(qe);
}

_QueueNode_ *_get_queue_node_(Queue *qe, size_t index)
{
    if (!qe->first)
    {
        return NULL;
    }
    if (index < 0 || index >= qe->size)
    {
        return NULL;
    }
    
    _QueueNode_ *tmplast = NULL;
    _QueueNode_ *tmp = qe->first;
    size_t nowi = 0;
    do
    {
        if (index == nowi)
        {
            return tmplast;
        }
        tmplast = tmp;
        nowi++;
    }while (tmp = tmp->next);
    
    return NULL;
}

_QueueNode_* _queue_update_with_lastnode_(Queue *qe, _QueueNode_ *lastnode, void *value, int flags)
{
    int f = flags & UPDATE_NODE;
    _QueueNode_ *node = NULL;
    if (f == INSERT_NODE)
    {
        node = malloc(_QUEUE_NODE_TYPE_SIZE_);
        node->next = NULL;
        if (lastnode)
        {
            _QueueNode_ *tmpnext = lastnode->next;
            lastnode->next = node;
            node->next = tmpnext;
        }else
        {
            node->next = qe->first;
            qe->first = node;
        }
        qe->size++;
    }else if (f == UPDATE_NODE)
    {
        if (lastnode){
            node = lastnode->next;
        }else
        {
            node = qe->first;
        }
    }else
    {
        node = lastnode;
        _QueueNode_ *tmp = NULL;
        if (lastnode)
        {
            tmp = lastnode->next;
        }else
        {
            tmp = qe->first;
        }
        
        if (tmp)
        {
            if (flags & DELETE_WITH_VALUE)
            {
                free(tmp->value);
            }
            if (lastnode)
            {
                lastnode->next = tmp->next;
            }else
            {
                qe->first = tmp->next;
            }
            free(tmp);
        }else
        {
            if (lastnode)
            {
                qe->last = lastnode;
            }else
            {
                qe->first = NULL;
                qe->last = NULL;
            }
        }
        qe->size--;
    }
    
    if (f & INSERT_NODE)
    {
        if (flags & CREATE_NEW_VALUE)
        {
            node->value = create_replica(value, qe->type);
        }else
        {
            node->value = value;
        }
    }
    return node;
}

Queue *queue_update_arr_diy(Queue *qe, size_t start, size_t end, void *value, size_t len, int flags)
{
    if (start >= qe->size)
    {
        if (flags & INSERT_NODE)
        {
            return queue_concat_arr(qe, value, len, flags);
        }
        return qe;
    }else if (start > end && !end || (flags & INSERT_NODE) && !len)
    {
        return qe;
    }

    end = end > qe->size ? qe->size : end;

    _QueueNode_ *tmp = _get_queue_node_(qe, start);
    size_t step = 1;
    if (end)
    {
        step = end - start;
    }
    
    size_t index = 0;

    if (flags & UPDATE_NODE == UPDATE_NODE)
    {
        if (step > len)
        {
            index = len;
            flags = flags - INSERT_NODE;
        }else
        {
            index = step;
            flags = flags - DELETE_NODE;
        }
        
        for (size_t i = 0; i < index; i++)
        {
            tmp = _queue_update_with_lastnode_(qe, 
                    tmp, value+i*qe->type, flags);
        }
        
    }

    if (flags & DELETE_NODE)
    {
        for (; index < step; index++)
        {
            tmp = _queue_update_with_lastnode_(qe, 
                    tmp, value+index*qe->type, flags);
        }
        
    }else if (flags & INSERT_NODE)
    {
        for (; index < len; index++)
        {
            tmp = _queue_update_with_lastnode_(qe, 
                    tmp, value+index*qe->type, flags);
        }
    }
    
    return qe;
}

Queue *queue_update_diy(Queue *q1, Queue *q2, size_t start, size_t end, int flags)
{
    if (start >= q1->size)
    {
        if (flags & INSERT_NODE)
        {
            return queue_concat(q1, q2, flags);
        }
        return q1;
    }else if (start > end && !end)
    {
        return q1;
    }

    end = end > q1->size ? q1->size : end;

    _QueueNode_ *tmp = _get_queue_node_(q1, start);
    size_t step = 1;
    if (end)
    {
        step = end - start;
    }
    
    int f = DELETE_OLD_VALUE_CREATE_NEW & flags;
    if (flags & DELETE_NODE)
    {
        for (size_t index = 0; index < step; index++)
        {
            tmp = _queue_update_with_lastnode_(q1, 
                    tmp, NULL, f + DELETE_NODE);
        }
        
    }
    if (flags & INSERT_NODE)
    {
        if (q2->first)
        {
            if (flags & CLONE_NEW_QUEUE)
            {
                q2 = queue_clone_all(q2, flags);
            }
            
            if (tmp)
            {
                q2->last->next = tmp->next;
                tmp->next = q2->first;
            }else
            {
                q2->last->next = q1->first;
                q1->first = q2->first;
            }
            q1->size += q2->size;

            if (flags & CLONE_NEW_QUEUE)
            {
                q2->first = NULL;
                queue_destory(q2, NONE_FLAGS);
            }
        }
    }
    
    return q1;
}

_QueueNode_ *_clone_queue_node_(void *value, size_t size, int flags)
{
    _QueueNode_ *tmp = malloc(_QUEUE_NODE_TYPE_SIZE_);
    if (flags & CREATE_NEW_VALUE)
    {
        tmp->value = malloc(size);
        memcpy(tmp->value, value, size);
    }else
    {
        tmp->value = value;
    }
    tmp->next = NULL;
    return tmp;
}

Queue *queue_clone(Queue *qe, size_t start, size_t end, int flags)
{
    _QueueNode_ *tmp = qe->first;
    Queue *qecp = malloc(_QUEUE_TYPE_SIZE_);
    qecp->type = qe->type;
    qecp->size = qe->size;
    qecp->first = NULL;
    qecp->last = NULL;

    if (!qe->first || start >= qe->size || start >= end)
    {
        return qecp;
    }
    
    _QueueNode_ *tmpnew;
    size_t index = 0;
    do
    {
        if (index == start)
        {
            tmpnew = _clone_queue_node_(tmp->value, qe->type, flags);
            qecp->first = tmpnew;
            qecp->last = tmpnew;
        }
        if (index > start)
        {
            tmpnew->next = _clone_queue_node_(tmp->value, qe->type, flags);
            tmpnew = tmpnew->next;
            qecp->last = tmpnew;
        }
        index++;
    } while ((tmp = tmp->next) && index < end);
    
    return qecp;
}

Queue *queue_clone_all(Queue *qe, int flags)
{
    return queue_clone(qe, 0, qe->size, flags);
}


void *queue_each(Queue *qe, void *arg, void *fun(Queue*,_QueueNode_*,_QueueNode_*,_QueueNode_**,size_t,void*,void*))
{
    if (!qe->first)
    {
        return NULL;
    }

    _QueueNode_ *tmplaqe = NULL;
    _QueueNode_ *tmp = qe->first;
    _QueueNode_ *tmpnext = NULL;
    size_t index = 0;
    void *result = NULL;
    do
    {
        tmpnext = tmp->next;
        result = fun(qe, tmplaqe, tmp, &tmpnext, index, arg, result);
        tmplaqe = tmp;
        tmp = tmpnext;
        index++;
    } while (tmp);
    
    return result;
}