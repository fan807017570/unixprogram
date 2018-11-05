/*
 * https://www.ibm.com/support/knowledgecenter/en/ssw_ibm_i_72/rzab6/xnonblock.htm
 *   http://developerweb.net/viewtopic.php?id=2933
 */
#include <stdlib.h>
#include<stdio.h>
#include<netinet/in.h>
#include<errno.h>
#include<sys/ioctl.h>
#include<sys/time.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<string.h>
#include<sys/select.h>
#include<unistd.h>
#define SERVER_PORT 8090
#define     TRUE    1 
#define     FALSE   0
#define     BUF_LEN 100
int main(int argc ,char ** argv){
    int sfd,max_sd=-1,cfd;
    int on=1,rc,desc_ready=-1,i;
    int close_conn;
    char buffer[BUF_LEN];
    fd_set master_set ,working_set;
    struct timeval timeout;
    struct sockaddr_in saddr,cliaddr;
    sfd=socket(AF_INET,SOCK_STREAM,0);
    if(sfd<0){
        printf("socket failed error:%s",strerror(errno));
        return -1;
    }
    rc=ioctl(sfd,FIONBIO,(char *)&on);
    if(rc<0){
        printf("ioctl() failed :%s",strerror(errno));
        return -1;
    }
    rc = setsockopt(sfd,SOL_SOCKET,SO_REUSEADDR,(char*)&on,sizeof(on));
    if(rc<0){
        printf("setsockopt failed:%s\n",strerror(errno));
        return -1;
    }
    memset(&saddr,0,sizeof(struct sockaddr_in));
    saddr.sin_family=AF_INET;
    saddr.sin_addr.s_addr=inet_addr("127.0.0.1");
    saddr.sin_port=htons(SERVER_PORT);
    rc =bind(sfd,(struct sockaddr *)&saddr,sizeof(struct sockaddr));
    if(rc!=0){
        printf("bind error :%s \n",strerror(errno));
        close(sfd);
        return -1;
    }
    rc=listen(sfd,10);
    if(rc==-1){
        printf("listen error :%s \n",strerror(errno));
        close(sfd);
        return -1;
    }
    FD_ZERO(&master_set);
    max_sd=sfd;
    FD_SET(sfd,&master_set);
    timeout.tv_sec=3*60;
    timeout.tv_usec=0;
    do{
        memcpy(&working_set,&master_set,sizeof(master_set));
        rc=select(max_sd+1,&working_set,NULL,NULL,&timeout);
        if(rc<0){
            printf("select error:%s\n",strerror(errno));
            close(sfd);
            break;
        }
        if(rc==0){
            printf("select(0 timeout.end program\n");
            break;
        }
        desc_ready=rc;
        for(i=0;i<max_sd && desc_ready>0;++i){
            if(FD_ISSET(i,&working_set)){
                    if(i==sfd){
                        do{
                            cfd=accept(sfd,NULL,NULL);
                            if(cfd<0){
                                printf("accept error:%s \n",strerror(errno));
                                break;
                            }
                            FD_SET(cfd,&master_set);
                            if(cfd>max_sd)
                            {
                                max_sd=cfd;
                            }
                            desc_ready--;
                        }while(cfd!=-1);
                    }
                else{
                    // other descriptor is ready
                    close_conn=FALSE;
                    do{
                        rc=recv(i,buffer,sizeof(buffer),0);
                        if(rc<0){
                            if(errno!=EWOULDBLOCK){
                                printf("recv error:%s\n",strerror(errno));
                                close_conn=TRUE;
                            }
                            break;
                        }
                        if(rc==0){
                            printf("connection closed");
                            close_conn=TRUE;
                            break;
                        }
                        int len=rc;
                        printf("recv %d bytes\n",rc);
                        buffer[rc]='\n';
                        printf("recv data is :%s \n",buffer);
                        rc=send(i,buffer,len,0);
                        if(rc<0){
                            printf("send data error:%s\n",strerror(errno));
                            close_conn=TRUE;
                            break;
                        }
                    }while(TRUE);
                    if(close_conn==TRUE){
                        close(i);
                        FD_CLR(i,&master_set);

                    }
                }
            }
        }
    }while(TRUE);
}