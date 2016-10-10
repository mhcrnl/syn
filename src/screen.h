#ifndef __SCREEN_H__
#define __SCREEN_H__

#include"syn.h"

typedef void(*on_keypress_cb)(int key, syn_gbuffer_t *buffer);

/* initialize screen */
void syn_screen_init(syn_gbuffer_t *buffer);
/* draw a buffer to the screen */
void syn_screen_update();
/* what do we do on keypress ? */
void syn_screen_on_keypress(on_keypress_cb cb);
/* destroy the screen */
void syn_screen_destroy();

#endif
