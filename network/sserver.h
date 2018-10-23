// int select(int maxfdp1,fd_set *readset,fd_set *writeset,fd_set *exceptset,const struct timeval *timeout)
// include<sys/select.h>
// include<sys/time.h>
// fd_set rset
// void FD_ZERO(fd_set * rset)
// void FD_SET(1,&rset)
// void FD_SET(4,&rset)
#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<errno.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/select.h>
#define SERVER_PORT 8089
#define MAX_LEN 1024