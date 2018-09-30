#include <stdio.h>
#include <sys/socket.h>
#include <string.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include<errno.h>
#define SERVER_PORT 8097
#define MAX_LEN 2049
void str_echo(int fd);
ssize_t writen(int fd, const void *vptr, size_t n);
ssize_t readn(int fd, const void *vptr, size_t n);