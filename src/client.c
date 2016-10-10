#include<uv.h>
#include<math.h>
#include<string.h>
#include<unistd.h>

#include"syn.h"
#include"mem.h"
#include"buffer.h"
#include"screen.h"

#define usage() fputs("Usage: syn [SESSION_ID HOST]", stderr); exit(1);


void on_keypress(int key, syn_gbuffer_t *buffer)
{
    syn_gbuffer_insert(buffer, (char)key);
    syn_gbuffer_advance_cursor(buffer, 1);
}

int client_main(int argc, char **argv)
{
    debug_n("Running client");
    u(argv);
    if(argc < 3){
	usage();
    }
    syn_gbuffer_t *buffer = syn_gbuffer_create();

    syn_screen_init(buffer);

    syn_screen_on_keypress(on_keypress);

    syn_screen_update();

    syn_screen_destroy();

    /* destroy buffer */
    syn_gbuffer_destroy(buffer);

    return 0;
}
