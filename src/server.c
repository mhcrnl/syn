#include<uv.h>

#include"syn.h"
#include"config.h"
#include"mem.h"

#define rmrn(buf, size) buf[size - 2] = '\0'

static uv_loop_t *loop;
static uv_tcp_t *server_handle;

void on_close(uv_handle_t *handle)
{
    syn_free(handle);
}

/* uv_stream_t on read callback */
void echo_read(uv_stream_t *stream, ssize_t nread, const uv_buf_t *buf)
{
    if(nread < 0){
	uv_close((uv_handle_t *)stream, on_close);
	syn_free(buf->base);
	uv_close((uv_handle_t *)server_handle, on_close);
	return;
    }
    buf->base[nread - (nread > 2 ? 2 : 0)] = '\0';
    syn_free(buf->base);
}

/* buffer allocation callback */
void alloc_buffer(uv_handle_t *handle, size_t def, uv_buf_t *buf)
{
    u(handle);
    buf->base = syn_malloc(def);
    buf->len = def;
}

/* client_handle connection callback */
void on_client_connect(uv_stream_t *server_stream, int status)
{
    if(status < 0){
	debug_fn("New connection error \"%s\"", uv_strerror(status));
	return;
    }
    debug_n("Client connected");

    uv_tcp_t *client_handle = syn_malloc(sizeof(uv_tcp_t));
    uv_tcp_init(loop, client_handle);
    if(!uv_accept(server_stream, (uv_stream_t *)client_handle)){
	/* the client_handle has been accepted */
	uv_read_start((uv_stream_t *)client_handle, alloc_buffer, echo_read);
    }else{
	/* error occured accepting the client_handle */
	uv_close((uv_handle_t *)client_handle, on_close);
    }
}


int server_main(int argc, char **argv)
{
    u(argc);
    u(argv);
    /* setup event loop */
    loop = syn_malloc(sizeof(uv_loop_t));
    uv_loop_init(loop);

    /* prepare listener handle */
    server_handle = syn_malloc(sizeof(uv_tcp_t));
    uv_tcp_init(loop, server_handle);
    
    /* create sockaddr_in from ip */
    struct sockaddr_in addr;
    uv_ip4_addr(SERVER_DEFAULT_IP, SERVER_DEFAULT_PORT, &addr);
    
    /* bind handler to port 8765 and listen for all connections */
    uv_tcp_bind(server_handle, (const struct sockaddr *)&addr, 0);

    /* the on_client_handle_connect handler will be invoked */
    int r = uv_listen((uv_stream_t *)server_handle, 10, on_client_connect);
    if(r){
	debug_fn("Listen error: \"%s\"", uv_strerror(r));
	return 1;
    }

    uv_run(loop, UV_RUN_DEFAULT);

    syn_free(loop);
    return 0;
}
