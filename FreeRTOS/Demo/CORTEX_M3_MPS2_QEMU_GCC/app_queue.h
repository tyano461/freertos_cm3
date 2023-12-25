#ifndef __APP_QUEUE_H__
#define __APP_QUEUE_H__

#include <sys/queue.h>
#include <stdint.h>

typedef struct str_queue
{
    TAILQ_ENTRY(str_queue)
    entry;
    size_t len;
    uint8_t data[0];
} queue_t;

queue_t *dequeue(void);
void enqueue(queue_t *data);
queue_t *peek_queue(void);

#endif