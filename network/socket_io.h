#include <stdio.h>
#include <sys/socket.h>
#include <string.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include<errno.h>
ssize_t writen(int fd, const void *vptr, size_t n);
ssize_t readn(int fd, const void *vptr, size_t n);
ssize_t readline(int fd, void *vptr,size_t maxlen);