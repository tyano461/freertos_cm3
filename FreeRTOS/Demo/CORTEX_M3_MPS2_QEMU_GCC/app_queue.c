#include "app_common.h"
#include "app_queue.h"

static TAILQ_HEAD(tq_head, str_queue) head;

queue_t *dequeue(void)
{
    queue_t *data;
    taskENTER_CRITICAL();
    data = (queue_t *)TAILQ_FIRST(&head);
    if (data)
    {
        TAILQ_REMOVE(&head, data, entry);
    }
    taskEXIT_CRITICAL();
    return data;
}

void enqueue(queue_t *queue)
{
    if (queue && *queue->data)
    {
        taskENTER_CRITICAL();
        TAILQ_INSERT_TAIL(&head, queue, entry);
        taskEXIT_CRITICAL();
    }
}

queue_t *peek_queue(void)
{
    return (queue_t *)TAILQ_FIRST(&head);
}