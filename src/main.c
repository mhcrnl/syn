#include"syn.h"
#include<uv.h>

int main(int argc, char **argv)
{
    u(argv);
    debug_n("Starting with %d arg%s", argc, pluralize(argc));
    uv_loop_t *loop = uv_default_loop();
    uv_loop_init(loop);


    return uv_run(loop, UV_RUN_DEFAULT);
}

