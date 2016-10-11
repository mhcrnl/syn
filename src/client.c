#include"syn.h"
#include"mem.h"
#include"buffer.h"
#include"screen.h"

#define usage() fputs("Usage: syn [SESSION_ID HOST]", stderr); exit(1);

int client_main(int argc, char **argv)
{
    u(argv);
    if(argc < 3){
	usage();
    }

    syn_screen_init();

    while(!syn_screen_update());

    syn_screen_destroy();

    return 0;
}
