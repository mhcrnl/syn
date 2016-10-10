#include"_linux.h"

#include<unistd.h>
#include<stdlib.h>

#include<ncurses.h>
#include"syn.h"
#include"buffer.h"

#define KEY_ESC 27

static on_keypress_cb on_keypress = NULL;
static syn_gbuffer_t *_buffer;

void syn_screen_init(syn_gbuffer_t *buffer)
{
    /* set escape delay to zero */
    if(!getenv("ESCDELAY")){
	putenv("ESCDELAY=25");
    }

    initscr();
    noecho();
    cbreak();
    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE);
    /* set internal buffer */
    _buffer = buffer;
}

static void draw_char(char c, int l)
{
    u(l);
    addch(c);
}

void do_key(int key)
{
    switch(key){
    case KEY_LEFT:
	syn_gbuffer_advance_cursor(_buffer, -1);
	return;
    case KEY_RIGHT:
	syn_gbuffer_advance_cursor(_buffer, 1);
	return;
    /* TODO implement a better system for navigation */
    case KEY_UP:
	break;
    case KEY_DOWN:
	break;
    default:
	on_keypress(key, _buffer);
	break;
    }
}

void syn_screen_update()
{
    if(!_buffer){
	debug_n("ERROR");
	return;
    }
    int ch = 0;
    while(1){
	refresh();
	if((ch = getch()) != ERR){
	    refresh();
	    if(ch == KEY_ESC){
		return;
	    }
	    do_key(ch);
	    move(0, 0);
	    syn_gbuffer_walk(_buffer, draw_char);
	}
	move(0, _buffer->cursor);
	usleep(16666);
    }
}

void syn_screen_on_keypress(on_keypress_cb cb)
{
    on_keypress = cb;
}

void syn_screen_destroy()
{
    endwin();
}
