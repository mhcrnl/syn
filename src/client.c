#include<uv.h>
#include<math.h>
#include<string.h>

#include"syn.h"
#include"mem.h"
#include"screen.h"

#define usage() fputs("Usage: syn [SESSION_ID HOST]", stderr); exit(1);


int client_main(int argc, char **argv)
{
    if(argc != 3){
	usage();
    }
    syn_uuid_t session_id = atoi(argv[1]);	/* get session id */
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
    
    syn_screen_init();
    syn_screen_draw(NULL);
    syn_screen_destroy();

    return 0;
}
