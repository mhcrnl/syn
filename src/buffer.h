#ifndef __BUFFER_H__
#define __BUFFER_H__

#include"syn.h"

/* create a buffer */
syn_gbuffer_t *syn_gbuffer_create();
/* move cursor to position in the buffer */
void syn_gbuffer_move_cursor(syn_gbuffer_t *buffer, int to);
/* move cursor x step(s) */
void syn_gbuffer_advance_cursor(syn_gbuffer_t *buffer, int i);
/* insert character into buffer */
void syn_gbuffer_insert(syn_gbuffer_t *buffer, char c);
/* insert string into buffer */
void syn_gbuffer_insert_str(syn_gbuffer_t *buffer, char *str);
/* delete character from buffer */
char syn_gbuffer_delete(syn_gbuffer_t *buffer);
/* draw a buffer */
void syn_gbuffer_walk(syn_gbuffer_t *buffer, void(*per)(char, int));
/* destroy a buffer */
void syn_gbuffer_destroy(syn_gbuffer_t *buffer);

#endif
