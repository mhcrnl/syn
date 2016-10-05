#ifndef __MEM_H__
#define __MEM_H__

/*      mem.h 
 * defines methods for checked memory allocation 
 */

#include<stdio.h>
#include<stdlib.h>

void *syn_malloc(size_t bytes);    
void *syn_calloc(size_t size, size_t bytes);
void *syn_realloc(void *data, size_t size);
void syn_free(void *data);    


#endif
