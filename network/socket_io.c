#include"socket_io.h"
ssize_t writen(int fd, const void *vptr, size_t n)
{
    int nleft = n;
    int nwriten = 0;
    const void *ptr = vptr;
    while (nleft > 0)
    {
        if ((nwriten = write(fd, vptr, nleft) <= 0))
        {
            if (nwriten < 0 &&errno == EINTR)
            {
                nwriten = 0;
            }
            else
            {
                return -1;
            }
        }
        nleft -= nwriten;
        ptr += nwriten;
    }
    return n;
}
ssize_t readn(int fd, const void *vptr, size_t n)
{
    // 从socket中读取数据
    int nleft;
    int nread;
    nread = n;
    const void *ptr;
    while (nleft > 0)
    {
        if ((nread = read(fd, ptr, nleft)) < 0)
        {
            if (nread < 0 &&errno == EINTR)
            {
                nread = 0;
            }
            else
            {
                return -1;
            }
        }
        nleft -= nread;
        ptr = ptr + nread;
    }
    return n;
}