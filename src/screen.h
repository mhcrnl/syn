#ifndef __SCREEN_H__
#define __SCREEN_H__

#include"syn.h"

/* initialize screen */
void syn_screen_init();
/* draw a buffer to the screen */
int syn_screen_update();
/* destroy the screen */
void syn_screen_destroy();

#endif
