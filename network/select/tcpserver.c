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
#define SERVER_PORT 8090
#define     TRUE    1 
#define     FALSE   0
int main(int argc ,char ** argv){
    int sfd,max_sd=-1,cfd;
    int on=1,rc,desc_ready=-1,i;
    fd_set master_set ,working_set;
    struct timeval timeout;
    struct sockaddr_in saddr,cliaddr;
    sfd=socket(AF_INET,SOCK_STREAM,0);
    rc=ioctl(sfd,FIONBIO,(char *)&on);
    if(rc<0){
        perror("ioctl() failed:%s",strerror(errno));
        return -1;
    }
    rc = setsockopt(sfd,SOL_SOCKET,SO_REUSEADDR,(char*)&on,sizeof(on))
    if(rc<0){
        perror("setsockopt failed:%s\n",strerror(errno));
        return -1;
    }
    if(sfd<0){
        perror("socket() failed :%s\n",strerror(errno));
        return -1;
    }
    memset(&saddr,0,sizeof(struct sockaddr_in));
    saddr.sin_family=AF_INET;
    saddr.sin_addr.s_addr=inet_addr("127.0.0.1");
    saddr.sin_port=htons(SERVER_PORT);
    rc =bind(sfd,(struct sockaddr *)&saddr,sizeof(struct sockaddr));
    if(rc!=0){
        perror("bind error :%s \n",strerror(errno));
        close(sfd);
        return -1;
    }
    rc=listen(sfd,10);
    if(rc==-1){
        perror("listen error :%s \n",strerror(errno));
        close(sfd);
        return -1;
    }
    FD_ZERO(&master_set);
    max_sd=sfd;
    FD_SET(SFD,&master_set);
    timeout.tv_sec=3*60;
    timeout.tv_usec=0;
    do{
        memcpy(&working_set,&master_set,sizeof(master_set));
        rc=select(max_sd+1,&working_set,NULL,NULL,&timeout);
        if(rc<0){
            perror("select error:%s\n",strerror(errno));
            close(sfd);
            break;
        }
        if(rc==0){
            printf("select(0 timeout.end program\n");
            break;
        }
        desc_ready=rc;
        for(i=0;i<max_sd && desc_ready>0;++i){
            if(FD_ISSET(i,working_set)){
                desc_ready--;
                if(i==sfd){
                    //listen descriptor  is ready
                    cfd=accept(sfd,NULL,NULl);
                    if(cfd<0){
                        perror("accept faild :%s \n",strerror(errno));
                        close(sfd);
                        break;
                        // return -1;
                    }else{

                    }

                }else{
                    // other descriptor is ready

                }
            }

        }


    }while()
    
}