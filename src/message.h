#ifndef __MESSAGE_H__
#define __MESSAGE_H__

#include"syn.h"

/* create message of type */
syn_message_t *syn_message_create(syn_message_type_t type);
/* destroy message */
void syn_message_destroy(syn_message_t *message);
/* serialize a message for passing over network */
int syn_serialize_message(syn_message_t *message, void *dest, size_t size);

/* create a message queue */
syn_message_queue_t *syn_message_queue_create();
/* push a message onto the queue */
int syn_message_queue_push(syn_message_queue_t *queue, syn_message_t message);
/* pop a message from the queue */
int syn_message_queue_pop(syn_message_queue_t *queue, syn_message_t *result);
/* destroy a message queue */
void syn_message_queue_destroy(syn_message_queue_t *queue);

#endif
