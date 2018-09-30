#include<stdio.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<string.h>
#include<errno.h>
int main(int argc,char ** argv){
    char [] ip=argv[1];
    if(strlen(ip)==0){
        printf("sorry please input server ip\n");
        return -1;
    }
    char * port =argv[2];
    if(strlen(port)){
        printf("sorry ,please input server prot \n");
        return -1;
    }
    int port =itoa(port);
    int cfd;
    socket_t len;
    struct sockadd_in addr;
    bzero(&addr,sizeof(struct sockaddr_in));
    addr.sin_family=AF_INET;
    add.sin_port=htons(port)
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    cfd=socket(AF_INET,SOCK_STREAM,0);
    len =sizeof(addr);
    int ret=connect(cfd,(struct sockaddr *)&addr,&len);
    if(ret<0){
        printf("connect server error %d \n",errno);
        return -1;
    }
    str_cli(stdin,cfd);
    return 0;
}

void str_cli(int stdin,int fd){


}