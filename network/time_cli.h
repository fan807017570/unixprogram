#include<stdio.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<string.h>
#include<errno.h>
#include<stdlib.h>
#include"socket_io.h"
#define MAX_LEN 2049
void str_cli(FILE * stdin,int fd);