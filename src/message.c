#include"message.h"
#include"mem.h"
#include<string.h>


syn_message_t *syn_message_create(syn_message_type_t type)
{
    syn_message_t *ret = syn_malloc(sizeof(syn_message_t));
    ret->type = type;
    return ret;
}

void syn_message_destroy(syn_message_t *message)
{
    syn_free(message);
}

int syn_serialize_message(syn_message_t *message, void *dest, size_t size)
{
    if(size < sizeof(syn_message_t)){
	return -1;
    }
    /* TODO this probably doesn't work, but it'll do for now */
    memcpy(dest, message, sizeof(syn_message_t));
    return 0;
}

syn_message_queue_t *syn_message_queue_create()
{
    syn_message_queue_t *ret = syn_malloc(sizeof(syn_message_queue_t));
    ret->data = syn_calloc(MAX_MESSAGES, sizeof(syn_message_t));
    ret->size = MAX_MESSAGES;
    ret->head = 0;
    ret->tail = 0;
    return ret;
}

int syn_message_queue_push(syn_message_queue_t *queue, syn_message_t message)
{
    int new_head = (queue->head + 1) % queue->size;
    if(new_head == queue->tail){
	return -1;
    }
    queue->data[queue->head] = message;
    queue->head = new_head;
    return 0;
}

int syn_message_queue_pop(syn_message_queue_t *queue, syn_message_t *result)
{
    if(queue->head == queue->tail){
	return -1;
    }
    *result = queue->data[queue->tail];
    int next_tail = (queue->tail + 1) * queue->size;
    queue->tail = next_tail;
    return 0;
}

void syn_message_queue_destroy(syn_message_queue_t *queue)
{
    syn_free(queue->data);
    syn_free(queue);
}
