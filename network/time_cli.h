#include<stdio.h>
#include<stdlib.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#include <netinet/in.h>
#include<sys/types.h>
#include<string.h>
#include<errno.h>
#include<stdlib.h>
#include<unistd.h>
#include"socket_io.h"
#include<errno.h>
#define MAX_LEN 2049
void str_cli(FILE * stdin,int fd);
