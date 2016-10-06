#ifndef __CONFIG_H__
#define __CONFIG_H__

#include<stdio.h>

typedef struct client_config_s {
    char *editor_config;
    /* file to read editor config from */
    char *log_file;
    /* file to log to */
    long timeout;
    /* socket timeout when connecting to server */
} client_config_t;

typedef struct server_config_s {
    unsigned short port;
    /* port to listen on */
    unsigned short conn_max;
    /* maxumum connections allowed to server */
    unsigned short session_max;
    /* maximum sessions per server */
    unsigned short session_conn_max;
    /* maximum sessions per server */
    unsigned short change_backlog;
    /* maximum change backlog */
} server_config_t;

/* parse a server config file */
int parse_sconf(server_config_t *cfg, FILE *file);
/* parse a client config file */
int parse_cconf(client_config_t *cfg, FILE *file);

#endif
