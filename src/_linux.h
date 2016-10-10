#ifndef __LINUX_H__
#define __LINUX_H__

#include"syn.h"
#include"screen.h"

/* TODO how will regex be implemented across multiple lines */

typedef struct syn_display_buffer_s syn_display_buffer_t;

typedef struct syn_display_buffer_s {
    syn_gbuffer_t *buffer;
    /* character buffer */
    syn_location_t cursor_loc;
    /* current location of the cursor on screen */
    int rows;
    /* rows in display buffer */
    int cols;
    /* columns in display buffer */
    int dirty;
    /* has the file been edited? */
    syn_display_buffer_t *next;
    /* next display buffer */
    syn_display_buffer_t *prev;
    /* previous buffer */
} syn_display_buffer_t;


typedef struct syn_editor_ctx_s {
    syn_display_buffer_t *display;
    /* currently open buffer */
    int num_buffers;
    /* number of buffers */
} syn_editor_ctx_t;

#endif
