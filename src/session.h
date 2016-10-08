#ifndef __SESSION_H__
#define __SESSION_H__

#include"syn.h"

syn_session_t *syn_session_create();
void syn_session_destroy(syn_session_t *syn_session);
/* create a session within a thread */
void syn_session_start(syn_session_t *syn_session);

#endif
