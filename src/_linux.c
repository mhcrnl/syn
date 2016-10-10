/* _LINUX.C
 * This file contains linux-specific code
 */
#include"_linux.h"

#include<unistd.h>
#include<stdlib.h>

#include<ncurses.h>
#include"syn.h"
#include"buffer.h"

/******************SCREEN*****************/

#define KEY_ESC 27

void syn_screen_init()
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
}

int do_key(int key)
{
    switch(key){
    case KEY_ESC:
	return 1;
    case KEY_BACKSPACE:
	return 0;
    case KEY_LEFT:
	return 0;
    case KEY_RIGHT:
	return 0;
    case KEY_UP:
	return 0;
    case KEY_DOWN:
	return 0;
    default:	/* supposedly an alphanumeric character */
	return 0;
    }
    return 0;
}

int syn_screen_update()
{
    int ch = 0;
    if((ch = getch()) != ERR){
	if(do_key(ch)){
	    return 1;
	}
	refresh();
    }
    return 0;
}

void syn_screen_destroy()
{
    endwin();
}
