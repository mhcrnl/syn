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

#define SERVER_DEFAULT_PORT 8765

#define fatal(x) fputs(stderr, x "\n"); exit(1);

#define pluralize(num) num != 1 ? "s" : ""

int server_main(int argc, char **argv);
int client_main(int argc, char **argv);

/* type for unique ids */
typedef uint32_t syn_uuid_t;

/* holds data for io transactions */
typedef struct io_s {
    const FILE *in;
    /* input for io */
    const FILE *out;
    /* output for io */
} io_t;

#define MAX_BROADCAST 32
/* type for multicast operations */
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
    char *chars;
    /* what data was added? */
    char *file;
    /* what file was changed? */
    syn_location_t loc;
    /* where did this change occur in the buffer? */
} syn_change_data_t;

/* allowances on currently viewed file 
 * If another user is editing the file
 * then this user is not allowed to edit */
#define READ_P 	1
#define WRITE_P	2	/* write permissions also allows deleting the file */
typedef uint8_t fflags_t;

/* file handle to read and write to
 * obtained through open_file()
 * and destroyed through close_file() */
typedef struct syn_file_s {
    fflags_t flags;
    /* permissions */
    uv_file file;	
    /* file to read and write to */
    /* TODO change to uv_fs_t or uv_file? gotta learn more about libuv */
} syn_file_t;

/********************SERVER********************/

typedef struct syn_session_s syn_session_t;

/* server context */
typedef struct syn_server_ctx_s {
    syn_session_t *sessions;
    /* active sessions */
    uv_thread_t *session_threads;
} syn_server_ctx_t;

/* a client in a session */
typedef struct syn_client_s {
    uv_tcp_t *handle;
    /* handle to client socket */
    char *name;
    /* client nickname */
    syn_uuid_t id;
    /* 32 bit client id  */
} syn_client_t;

/*
 * A session of syn on the server 
 * Holds pending changes, filesystem info, and a list of clients */
typedef struct syn_session_s {
    syn_uuid_t session_id;
    /* session id */
    uv_loop_t *loop;
    /* event loop */
    syn_client_t **clients;
    /* clients in the session */
    struct {
	syn_change_data_t *change_data;
	int head;
	int tail;
	int size;
	int cap;
    } change_queue;
    /* queue of changes to make */
} syn_session_t;

typedef enum syn_message_type_e {
    JOIN = 0,
    CREATE
} syn_message_type_t;

typedef struct syn_message_s {
    /* message id, used for response */
    syn_message_type_t type;
    /* type of the message */
    union syn_message_data_u {
	struct {

	} session_create_data;   
	struct {
	
	} session_join_data;
	struct {
	
	} request_file_data;
	struct {
	    syn_change_data_t change;
	} new_change_data;
    } data;
    /* message data */
} syn_message_t;

/* ring buffer as queue implementation */
#define MAX_MESSAGES 128
typedef struct syn_message_queue_s {
    syn_message_t *data;
    /* messages in queue */
    int size;
    /* buffer size */
    int head;
    /* head of the buffer */
    int tail;
    /* tail of the buffer */
} syn_message_queue_t;

/********************TEXT EDITOR********************/

/* gap buffer for text editing */
typedef struct syn_gbuffer_s {
    char *buffer;
    /* buffer (no shit) */
    int gap_start;
    /* start of the gap, points to first invalid character in gap */
    int gap_end;
    /* end of the gap, points to first valid character after gap */
    int capacity;
    /* memory size of the buffer */
    int size;
    /* amount of characters in the buffer */
    int cursor;
    /* cursor position */
} syn_gbuffer_t;

#endif
