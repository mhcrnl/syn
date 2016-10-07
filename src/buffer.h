#ifndef __BUFFER_H__
#define __BUFFER_H__

#include"syn.h"

/* create a buffer */
syn_gbuffer_t *syn_gbuffer_create();
/* insert character into buffer */
void syn_gbuffer_insert(syn_gbuffer_t *buffer, int position, char c);
/* delete character from buffer */
char syn_gbuffer_delete(syn_gbuffer_t *buffer, int position);
/* destroy a buffer */
void syn_gbuffer_destroy(syn_gbuffer_t *buffer);

#endif
