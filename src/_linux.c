#include"_linux.h"

#include<ncurses.h>
#include"syn.h"
#include"buffer.h"

void syn_screen_init()
{
    initscr();
    raw();	/* turn off ctrl-z and ctrl-c signals */
    noecho();	/* dont echo keys into the window */
    keypad(stdscr, TRUE);	/* detect keypad operations */
}

static void draw_char(char c, int l)
{
    u(l);
    addch(c);
}

void syn_screen_draw(syn_gbuffer_t *buffer)
{
    if(!buffer){
	return;
    }
    syn_gbuffer_walk(buffer, draw_char);
    move(0, 0);
}

void syn_screen_destroy()
{
    endwin();
}
