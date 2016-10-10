#include"buffer.h"

#include<string.h>

#include"mem.h"

#define DEFAULT_CAPACITY 64 
syn_gbuffer_t *syn_gbuffer_create()
{
    syn_gbuffer_t *ret = syn_malloc(sizeof(syn_gbuffer_t));
    /* set up buffer */
    ret->size = 0;
    ret->buffer = syn_calloc(DEFAULT_CAPACITY, sizeof(char));
    ret->capacity = DEFAULT_CAPACITY;
    ret->cursor = 0;
    /* gap start and end */
    ret->gap_start = 0;
    ret->gap_end = DEFAULT_CAPACITY - 1;
    return ret;
}
#undef DEFAULT_CAPACITY

/* move start of gap to a new position */
static inline void move_gap(syn_gbuffer_t *buffer, int to)
{
    /* amount of bytes in the gap */
    int gap_len = buffer->gap_end - buffer->gap_start;
    /* actual index of character in the buffer */
    if(buffer->gap_start == to){
        return;
    }
    if(buffer->gap_start > to){
	/* moving to location before gap */
	int distance = buffer->gap_start - to;
	/* copy characters to end of gap */
	memmove(buffer->buffer + buffer->gap_end - distance, 
		buffer->buffer + to, distance);
	buffer->gap_start -= distance;
	buffer->gap_end -= distance;
    }else{
	/* moving to location after gap, therefore, we need actual location */
	int character_loc = to + gap_len;
	/* because gap_end points to first valid character after gap */
	int distance = character_loc - buffer->gap_end;
	memmove(buffer->buffer + buffer->gap_start, 
		buffer->buffer + buffer->gap_end, distance);
	buffer->gap_start += distance;
	buffer->gap_end += distance;
    }
}

void syn_gbuffer_move_cursor(syn_gbuffer_t *buffer, int to)
{
    if(to > buffer->size){
	buffer->cursor = buffer->size;
    }else if(to < 0){
	buffer->cursor = 0;
    }else{
	buffer->cursor = to;
    }
}

void syn_gbuffer_advance_cursor(syn_gbuffer_t *buffer, int i)
{
    syn_gbuffer_move_cursor(buffer, buffer->cursor + i);
}

/* new gap allocation size */
#define GAP_SIZE 128
void syn_gbuffer_insert(syn_gbuffer_t *buffer, char c)
{
    move_gap(buffer, buffer->cursor);
    if(buffer->gap_end - buffer->gap_start == 0){
	/* realloc new gap */
	buffer->buffer = syn_realloc(buffer->buffer, 
				     buffer->capacity + GAP_SIZE);
	int size = buffer->capacity - buffer->gap_end;
	buffer->capacity += GAP_SIZE;
	/* move data to end of gap */
	memmove(buffer->buffer + buffer->capacity - size, 
		buffer->buffer + buffer->gap_end, size);
	buffer->gap_end += GAP_SIZE;
    }
    buffer->buffer[buffer->gap_start] = c;
    ++buffer->gap_start;
    ++buffer->size;
}
#undef GAP_SIZE

void syn_gbuffer_insert_str(syn_gbuffer_t *buffer, char *str)
{
    u(buffer);
    u(str);
}

char syn_gbuffer_delete(syn_gbuffer_t *buffer)
{
    /* move gap to position provided, then 
       move the start of the gap back one character */
    /* TODO what to do if the start is at 0? */
    /* move gap_start back one character */
    move_gap(buffer, buffer->cursor);
    --buffer->gap_start;
    --buffer->size;
    return buffer->buffer[buffer->gap_start + 1];
}

void syn_gbuffer_walk(syn_gbuffer_t *buffer, void(*per)(char, int))
{
    int location = 0;
    for(int i = 0; 
	location < buffer->size && i < buffer->capacity; 
	++i, ++location){
	if(i == buffer->gap_start){
	    i = buffer->gap_end;
	}
	per(buffer->buffer[i], location);
    }
}

void syn_gbuffer_destroy(syn_gbuffer_t *buffer)
{
    if(buffer){
	syn_free(buffer->buffer);
	syn_free(buffer);
	return;
    }
}
