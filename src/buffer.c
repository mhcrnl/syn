#include"buffer.h"

#include"mem.h"

#define DEFAULT_CAPACITY 64 
syn_gbuffer_t *syn_gbuffer_create()
{
    syn_gbuffer_t *ret = syn_malloc(sizeof(syn_gbuffer_t));
    /* set up buffer */
    ret->size = 0;
    ret->buffer = syn_calloc(DEFAULT_CAPACITY, sizeof(char));
    ret->capacity = DEFAULT_CAPACITY;
    /* gap start and end */
    ret->gap_start = 0;
    ret->gap_end = DEFAULT_CAPACITY;
    return ret;
}
#undef DEFAULT_CAPACITY

/* size of the gap */
#define GAP_SIZE 128
void syn_gbuffer_insert(syn_gbuffer_t *buffer, int position, char c)
{
    u(buffer);
    u(position);
    u(c);
}

char syn_gbuffer_delete(syn_gbuffer_t *buffer, int position)
{
    return buffer->buffer[position];
}

void syn_gbuffer_destroy(syn_gbuffer_t *buffer)
{
    if(buffer){
	syn_free(buffer);
    }
    debug_n("Attempt to destroy a null gbuffer");
}
