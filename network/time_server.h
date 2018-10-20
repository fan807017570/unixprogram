#include <stdio.h>
#include <sys/socket.h>
#include <string.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include<errno.h>
#include "socket_io.h"
#include "sum.h"
#define SERVER_PORT 8097
#define MAX_LEN 2049
void str_echo(int fd);
void add_echo(int fd);
// void sig_chld(int signo);