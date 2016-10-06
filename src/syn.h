#ifndef __SYN_H__
#define __SYN_H__

#include<stdio.h>
#include<stdint.h>
#include<stdlib.h>
#include<uv.h>

#define u(x) ((void)(x))

#ifdef DEBUG
#define debug_fn(fmt, ...) \
    fputs("DEBUG::> ", stderr); \
    fprintf(stderr, fmt, __VA_ARGS__); \
    fputc('\n', stderr)
#define debug_n(fmt) \
    fputs("DEBUG::> ", stderr); \
    fputs(fmt, stderr); \
    fputc('\n', stderr)
#else
#define debug_fn(fmt, ...)
#define debug_n(fmt)
#endif

#define pluralize(num) num != 1 ? "s" : ""

/* type for unique ids */
typedef uint32_t uuid_t;

/* holds data for io transactions */
typedef struct io_s {
    const FILE * in;
    /* input for io */
    const FILE * out;
    /* output for io */
} io_t;

#define MAX_BROADCAST 32
typedef struct multi_io_s {
    const FILE *in;
    /* input for io */
    const FILE *cast[MAX_BROADCAST];
    /* files to broadcast input to */
} multi_io_t;

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
 * then this user is not allowed to edit */
#define READ_P 	1
#define WRITE_P	2	/* write permissions also allows deleting the file */
typedef uint32_t fflags_t;

/* file handle to read and write to
 * obtained through open_file()
 * and destroyed through close_file() */
typedef struct syn_file_s {
    fflags_t flags;
    /* permissions */
    uv_file file;	
    /* file to read and write to */
    /* TODO change to uv_fs_t or uv_file? */
} syn_file_t;

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
 * Holds pending changes, filesystem info, and a list of clients */
typedef struct syn_session_s {
    uv_loop_t *loop;
    /* event loop */
    syn_client_t **clients;
    /* clients in the session */
    struct {
	syn_change_data_t *change_data;
	int size;
	int cap;
    } change_queue;
    /* queue of changes to make */
} syn_session_t;

#endif
