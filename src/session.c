#include"session.h"

#include"mem.h"

syn_session_t *syn_session_create()
{
    syn_session_t *ret = syn_malloc(sizeof(syn_session_t));
    return ret;
}

void syn_session_destroy(syn_session_t *syn_session)
{
    uv_loop_close(syn_session->loop);
    syn_free(syn_session->loop);
    syn_free(syn_session);
}

/* create a session within a thread */
void syn_session_start(syn_session_t *syn_session)
{
    u(syn_session);
}
