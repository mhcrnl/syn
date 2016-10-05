#include<uv.h>

#include"syn.h"
#include"config.h"



void on_client_connect()
{
    debug_n("Client connected");
}

int main(int argc, char **argv)
{
    debug_fn("Starting with %d argument%s", argc, pluralize(argc));
    int temp = argc;
    int index;
    while((index = (argc - temp--)) < argc){
	debug_fn("   ARG%d : %s", index, argv[index]);
    }

    uv_loop_t *loop = uv_default_loop();
    uv_loop_init(loop);

    debug_n("Running server event loop");
    return uv_run(loop, UV_RUN_DEFAULT);
}
