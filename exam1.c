#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/select.h>
#include <sys/time.h>

#define  FD_SIZE   3 
#define  FIFO1_PATH  "/tmp/fifo1"
#define  FIFO2_PATH  "/tmp/fifo2"
#define  MAX(a,b)    ((a>b)?a:b)

/* FD[2] use the stdin(fd=0)
    Hint:
        0 1 2
        i o e
*/

int main(){
    fd_set fdset;
    int fd[3];

    // 建立两个有名管道
    if(access(FIFO1_PATH,F_OK)){
        printf("No FIFO1, create new one\n");
        mkfifo(FIFO1_PATH,0600|O_CREAT);
    }
    if(access(FIFO2_PATH,F_OK)){
        printf("No FIFO2, create new one\n");
        mkfifo(FIFO2_PATH,0600|O_CREAT);
    }
    fd[0] = open(FIFO1_PATH,O_RDONLY|O_NONBLOCK);
    fd[1] = open(FIFO2_PATH,O_RDONLY|O_NONBLOCK);
    fd[2] = 0; // open("/dev/stdin",O_RDONLY|O_NONBLOCK);
    FD_ZERO(&fdset);
    FD_SET(fd[0],&fdset);
    FD_SET(fd[1],&fdset);
    FD_SET(fd[2],&fdset);
    // 初始化FD_SET，文件描述符集合，用于select/poll进行多路调用

    fd_set tmp_fdset; 
    // 3s 超时
    struct timeval delay_tv = {.tv_sec = 3};
    int maxfdlen = MAX(MAX(fd[0],fd[1]),fd[2]);
    int res;
	char text[128];

    // 初始状态，全部SET，当实际读空时，CLR从原始集合清除
	while(FD_ISSET(fd[0],&fdset)||FD_ISSET(fd[1],&fdset)||FD_ISSET(fd[2],&fdset)){
		delay_tv.tv_sec = 3;
        tmp_fdset = fdset;
		res = select(maxfdlen+1,&tmp_fdset,NULL,NULL,&delay_tv);
        if(res==-1){
            puts("Sel: Err while execute");
        }else if(res==0){
            puts("Sel: Timeout");
        }else{
            for(int i=0;i<3;i++){
                if(FD_ISSET(fd[i],&tmp_fdset)){
                    memset(text,0,sizeof(text));
                    int rbyte = read(fd[i],text,20);
                    if(rbyte<0) puts("Read Err");
                    else if(rbyte==0){
                        perror("read");
                        printf("FD[%d] reads null, close\n",i);
                        FD_CLR(fd[i],&fdset);
                        close(fd[i]);
                        // 关闭并清除句柄
                    }else{
                        // useful content
                        if(text[0]=='q') {
                            goto END;
                        }else{
                            printf("fd[%d]: %s\n",i,text);
                        }
                    }
                }
            }
		}
	}

END:
    close(fd[0]);
    close(fd[1]);
    close(fd[2]);
    // 删除FIFO，以unlink解耦
    unlink(FIFO1_PATH);
    unlink(FIFO2_PATH);

    return 0;
}
