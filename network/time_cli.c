#include"time_cli.h"
int main(int argc,char ** argv){
    char *ip =argv[1];
    if(strlen(ip)==0){
        printf("sorry please input server ip\n");
        return -1;
    }
    char * sport =argv[2];
    if(strlen(sport)){
        printf("sorry ,please input server prot \n");
        return -1;
    }
    int port;
    sprintf(argv[2],"%d",port);
    int cfd;
    socklen_t len;
    struct sockaddr_in addr;
    bzero(&addr,sizeof(struct sockaddr_in));
    addr.sin_family=AF_INET;
    addr.sin_port=htons(port);
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

void str_cli(FILE * fp,int fd){
    char sendline[MAX_LEN],recvline[MAX_LEN];
    while(fgets(sendline,MAX_LEN,fp)!=NULL){
        writen(fd,sendline,strlen(sendline));

    }
}