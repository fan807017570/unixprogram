#include"time_cli.h"
int main(int argc,char ** argv){
    printf("ip:%s ,prot %s\n",argv[1],argv[2]);
    char *ip =argv[1];
    if(strlen(ip)==0){
        printf("sorry please input server ip\n");
        return -1;
    }
    char * sport =argv[2];
    printf("input port is :%s",sport);
    if(strlen(sport)==0){
        printf("sorry ,please input server prot \n");
        return -1;
    }
    int port;
    port=atoi(sport);
    // sprintf(sport,"%d",port);
    int cfd;
    socklen_t len;
    struct sockaddr_in addr;
    bzero(&addr,sizeof(struct sockaddr_in));
    addr.sin_family=AF_INET;
    addr.sin_port=htons(port);
    addr.sin_addr.s_addr = htonl(ip);
    // printf("ip :%s \n",addr.sin_addr.s_addr);
    cfd=socket(AF_INET,SOCK_STREAM,0);
    len =sizeof(addr);
    int ret=connect(cfd,(struct sockaddr *)&addr,len);
    if(ret<0){ 
        printf("connect server error: %d \n",errno);
        return -1;
    }
    str_cli(stdin,cfd);
    return 0;
}

void str_cli(FILE * fp,int fd){
    char exit[] ="exit\n";
    printf("starting read from file %s ");
    char sendline[MAX_LEN],recvline[MAX_LEN];
    while(strlen(fgets(sendline,MAX_LEN,fp))>0){
        printf("send msg is :%s \n",sendline);
        if(strcmp(exit,sendline)==0){
            printf("program exit\n");
        }else{
        writen(fd,sendline,strlen(sendline));
        if(readline(fd,recvline,MAX_LEN)==0){
            printf("system terminated permaturely!");
        }
        fputs(recvline,stdout);
        }
    }
}
