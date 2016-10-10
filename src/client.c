#include<uv.h>
#include<math.h>
#include<string.h>

#include"syn.h"
#include"mem.h"

#define usage() fputs("Usage: syn [SESSION_ID HOST]", stderr); exit(1);

uv_loop_t *loop;

void on_write_end(uv_write_t *req, int status)
{
    u(req);
    if(status < 0){
	debug_fn("Error ending write: %s", uv_strerror(status));
	uv_close((uv_handle_t *)req->handle, NULL);
	return;
    }
    uv_close((uv_handle_t *)req->handle, NULL);
    syn_free(req);
}

void on_conn(uv_connect_t *req, int status)
{
    if(status < 0){
	debug_fn("Error connecting to server: %s", uv_strerror(status));
	return;
    }
    uv_stream_t *sock_stream = req->handle;
    char buffer[20];
    uv_buf_t buf = uv_buf_init(buffer, 100);
    buf.len = strlen("Hello from client\0") + 1;
    strncpy(buf.base, "Hello from client\0", buf.len);

    uv_write_t *write_req = syn_malloc(sizeof(uv_write_t));
    int buf_count = 1;
    uv_write(write_req, sock_stream, &buf, buf_count, on_write_end);
}

int client_main(int argc, char **argv)
{
    if(argc != 3){
	usage();
    }
    uuid_t session_id = atoi(argv[1]);	/* get session id */
    char *host_ip = argv[2];		/* get host ip */

    struct sockaddr_in addr;		/* server address */
    /* parse host ip from argv */
    int r = uv_ip4_addr(host_ip, SERVER_DEFAULT_PORT, &addr);
    if(r){
	printf("Invalid IP: \"%s\"\n", host_ip);
	return 1;
    }
    /* begin host connection */
    printf("Connecting to session %d on host %s\n", session_id, host_ip);
    
    loop = uv_default_loop();

    /* connect to server */
    uv_tcp_t *socket = syn_malloc(sizeof(uv_tcp_t));
    uv_tcp_init(loop, socket);
    uv_connect_t *connect = syn_malloc(sizeof(uv_connect_t));
    uv_tcp_connect(connect, socket, (const struct sockaddr *)&addr, on_conn);
    uv_run(loop, UV_RUN_DEFAULT);
    r = uv_loop_close(loop);
    syn_free(connect);
    syn_free(socket);
    if(r < 0){
	debug_fn("%s", uv_strerror(r));
    }
    return 0;
}
