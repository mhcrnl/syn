#ifndef __SCREEN_H__
#define __SCREEN_H__

#include"syn.h"

/* initialize screen */
void syn_screen_init();
/* draw a buffer to the screen */
void syn_screen_draw(syn_gbuffer_t *buffer);
/* destroy the screen */
void syn_screen_destroy();

#endif
