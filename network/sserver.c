#include"sserver.h"
int main(int argc,char ** argv){
    int sfd,connfd,sockfd;
    int maxfd,maxi,i,nready=0,rn=0;
    int client[FD_SETSIZE];
    char *ip;
    char buf[MAX_LEN];
    int ret;
    socklen_t len;
    fd_set allset,rset;
    // if(argc!=2){
    //     printf("input arguments error\n");
    //     return -1;
    // }
    struct sockaddr_in saddr,cliaddr;
    bzero(&saddr,sizeof(saddr));
    saddr.sin_family=AF_INET;
    // saddr.sin_addr.s_addr=htonl(INADDR_ANY);
    saddr.sin_addr.s_addr=inet_addr("127.0.0.1");
    saddr.sin_port=htons(SERVER_PORT);
    sfd=socket(AF_INET,SOCK_STREAM,0);
    ret=bind(sfd,(struct sockaddr*)&saddr,sizeof(saddr));
    if(ret!=0){
        printf("bind socket address error:%s\n",strerror(errno));
        return -1;
    }
    ret=listen(sfd,10);
    if(ret==-1){
        printf("listen error:%s\n",strerror(errno));
    }
    maxfd=sfd;
    maxi=-1;
    for(i=0;i<FD_SETSIZE;i++){
        client[i]=-1;
    }
    FD_ZERO(&allset);
    FD_SET(sfd,&allset);
    printf("socket server starting,listen port is :%d\n",SERVER_PORT);
    while(1){
        rset=allset;
        nready=select(maxfd+1,&rset,NULL,NULL,NULL);
        if(FD_ISSET(sfd,&allset)){
            len=sizeof(cliaddr);
            connfd=accept(sfd,(struct sockaddr *)&cliaddr,&len);
            for(i=0;i<FD_SETSIZE;i++){
                if(client[i]==-1){
                    client[i]=connfd;
                    break;
                }
            }
            if(i==FD_SETSIZE){
                printf("too many clients\n");
            }
            FD_SET(connfd,&allset);
            if(connfd>maxfd){
                maxfd=connfd;
            }
            if(maxi<i){
                maxi=i;
            }
            if(--nready<=0){
                continue;
            }
       }
        for(i=0;i<maxi;i++){
            if((sockfd=client[i])<0){
                continue;
            }
            if(FD_ISSET(client[i],&rset)){
                if((rn=read(sockfd,buf,MAX_LEN))==0){
                    close(sockfd);
                    FD_CLR(sockfd,&allset);
                    client[i]=-1;
                }else{
                    printf("read from client :%s\n",buf);
                    write(sockfd,buf,rn);
                }
                if(--nready<=0){
                    break;
                }
            }
        }
    }
    close(sfd);
    return 0;
}