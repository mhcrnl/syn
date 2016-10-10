#include<uv.h>

#include"syn.h"
#include"config.h"
#include"mem.h"

#define rmrn(buf, size) buf[size - 2] = '\0'

/* uv_stream_t on read callback */
void echo_read(uv_stream_t *stream, ssize_t nread, const uv_buf_t *buf)
{
    u(stream);
    if(nread < 0){
	debug_fn("Error reading from stream: %s", uv_strerror(nread));
	uv_close((uv_handle_t *)stream, NULL);
	return;
    }
    debug_fn("Received %s", buf->base);
}

/* buffer allocation callback */
void alloc_buffer(uv_handle_t *handle, size_t def, uv_buf_t *buf)
{
    u(handle);
    buf->base = syn_malloc(def);
    buf->len = def;
}

/* client connection callback */
void on_client_connect(uv_stream_t *server, int status)
{
    if(status < 0){
	debug_fn("New connection error \"%s\"", uv_strerror(status));
	return;
    }
    debug_n("Client connected");

    uv_tcp_t *client = syn_malloc(sizeof(uv_tcp_t));
    uv_tcp_init(uv_default_loop(), client);
    if(!uv_accept(server, (uv_stream_t *)client)){
	/* the client has been accepted */
	uv_read_start((uv_stream_t *)client, alloc_buffer, echo_read);
    }else{
	/* error occured accepting the client */
	uv_close((uv_handle_t *)client, NULL);
    }
}

int server_main(int argc, char **argv)
{
#ifdef DEBUG
    debug_fn("Starting with %d argument%s", argc, pluralize(argc));
    int temp = argc;
    int index;
    while((index = (argc - temp--)) < argc){
	debug_fn("   ARG%d : %s", index, argv[index]);
    }
#endif
    
    /* setup event loop */
    uv_loop_t *loop = uv_default_loop();
    uv_loop_init(loop);

    /* prepare listener handle */
    uv_tcp_t serv_handle;
    uv_tcp_init(loop, &serv_handle);
    
    /* create sockaddr_in from ip */
    struct sockaddr_in addr;
    uv_ip4_addr("0.0.0.0", SERVER_DEFAULT_PORT, &addr);
    
    /* bind handler to port 8765 and listen for all connections */
    uv_tcp_bind(&serv_handle, (const struct sockaddr *)&addr, 0);

    /* the on_client_connect handler will be invoked */
    int r = uv_listen((uv_stream_t *)&serv_handle, 10, on_client_connect);
    if(r){
	debug_fn("Listen error: \"%s\"", uv_strerror(r));
	return 1;
    }

    debug_n("Running server event loop");
    uv_run(loop, UV_RUN_DEFAULT);
    return 0;
}
