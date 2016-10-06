#include"syn.h"

int main(int argc, char **argv)
{
    if(argc >= 1){
	return client_main(argc, argv);
    }
    return server_main(argc, argv);
}
