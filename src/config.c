#include"config.h"
#include"syn.h"

#include<string.h>
#include<ctype.h>

int parse_sconf(server_config_t *cfg, FILE *file)
{
    u(cfg);
    char buf[1024];
    while(fgets(buf, 1024, file)){
	char *delim = strchr(buf, '\t');
	if(!delim){
	    debug_fn("Invalid attribute: \"%s\"", buf);
	    return 1;
	}
	*delim = '\0';
	char *attrib = buf;
	char *val = delim + 1;
	while(isspace(*val)){
	    ++val;
	}
	/* convert and assign value based on attrib */
	debug_fn("Encountered attribute %s of value %s", attrib, val);
    }
    return 0;
}

int parse_cconf(client_config_t *cfg, FILE *file)
{
    u(cfg);
    char buf[1024];
    while(fgets(buf, 1024, file)){
	char *delim = strchr(buf, '\t');
	if(!delim){
	    debug_fn("Invalid attribute: \"%s\"", buf);
	    return 1;
	}
	*delim = '\0';
	char *attrib = buf;
	char *val = delim + 1;
	while(isspace(*val)){
	    ++val;
	}
	debug_fn("Encountered attribute %s of value %s", attrib, val);
    }
    return 0;
}
