#include<stdio.h> 
#include<fcntl.h>
#include<errno.h>
#include<string.h>
#include<stdlib.h>
int main(int argc,char ** argv){
    char exit[]="exit\n";
    if(argc<2){
        printf("parameter error \n");
        return -1;
    }   
    int fd = open(argv[1],O_RDWR|O_APPEND|O_CREAT);
    if(fd==-1){
        printf("open file error %s\n",strerror(errno));
        return -1;
    }else{
        char buf[100],readbuf[1024];
        memset(readbuf,0,sizeof(buf));
       // while(read(0,readbuf,1024)>0){
        while(strlen(fgets(readbuf,1024,stdin))>0)
        {
            printf("content is :%s\n",readbuf);
            if(strcmp(exit,readbuf)==0){
                printf("program exit\n");
                return -1;
            }
            write(fd,readbuf,strlen(readbuf));
            memset(readbuf,0,sizeof(buf));
        }
        close(fd);
    }
    return 1;
}
