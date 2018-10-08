#include "time_server.h"
#include "socket_io.h"
int main(int argc, char **argv)
{
    //1.初始化socket和sockadd_sin地址
    int sfd, confd;
    pid_t pid;
    socklen_t len;
    struct sockaddr_in saddr, cliaddr;
    bzero(&saddr, sizeof(saddr));
    saddr.sin_family = AF_INET;
    saddr.sin_port = htons(SERVER_PORT);
    saddr.sin_addr.s_addr = htonl(INADDR_ANY);
    sfd = socket(AF_INET, SOCK_STREAM, 0);
    bind(sfd, (struct sockaddr *)&saddr, sizeof(struct sockaddr));
    listen(sfd, 10);
    printf("time server starting.....\n");
    len = sizeof(cliaddr);
    // confd = accept(sfd, (struct sockaddr *)&cliaddr, &len);
    // str_echo(confd);
    // close(confd);
    while (1)
    {
        //4.服务进程接受连接请求，并fork子进程处理
        confd = accept(sfd, (struct sockaddr *)&cliaddr, &len); //confd  parent proccess and child process  both have 
        if ((pid = fork()) == 0)
        {
            //如果是子进程，就执行请求处理函数
            printf("this process id is :%d\n",pid);
            close(sfd);
            str_echo(confd);
            exit(0);
        }
    }
    close(confd);
    return 0;
}
void str_echo(int fd)
{
    ssize_t  n;
    char buf[MAX_LEN];
    while((n=read(fd,buf,MAX_LEN))>0){
        printf("read content is :%s\n",buf);
        writen(fd,buf,n);
        if(n<0 && errno==EINTR){
            continue;
        }else if(n<0){
            printf("str echo :read error %d",errno);
        }
    }
}

