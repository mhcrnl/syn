#ifndef __SYN_H__
#define __SYN_H__

#include<stdio.h>
#include<uv.h>

#define u(x) ((void)(x))

#ifdef DEBUG
#define debug_n(fmt, ...); \
    fputs("DEBUG::> ", stderr); \
    fprintf(stderr, fmt, __VA_ARGS__); \
    fputc('\n', stderr);
#else
#define debug(fmt, ...)
#endif

#define pluralize(num) num != 1 ? "s" : ""

/* holds data for io transactions */
typedef struct io_s {
    /* input for io */
    const FILE * in;
    /* output for io */
    const FILE * out;
} io_t;

typedef struct syn_location_s {
    /* row in editor */
    int row;
    /* col in editor */
    int col;
} syn_location_t;

/* How changes made to the source file will be stored */
typedef struct syn_change_data_s {
    const char *chars;
    /* what data was added? */
    const char *file;
    /* what file was changed? */
    const syn_location_t loc;
    /* where did this change occur in the buffer? */
} syn_change_data_t;

/* allowances on currently viewed file 
 * If another user is editing the file
 * then this user is not allowed to edit
 */
typedef struct syn_file_permissions_s {
    char read: 1;
    /* can the user view/read this file? */
    char write: 1;
    /* can the user write/delete this file? */
} syn_file_permissions_t;

/* a client in a session */
typedef struct syn_client_s {
    uv_tcp_t *handle;
    /* handle to client socket */
    char *name;
    /* client nickname */
    uuid_t id;
    /* 32 bit client id  */
} syn_client_t;

/*
 * A session of syn on the server 
 * Holds pending changes, filesystem info, and a list of clients 
 */
typedef struct syn_session_s {
    uv_loop_t *loop;
    /* event loop */
    syn_client_t **clients;
    /* clients in the session */
} syn_session_t;

#endif
