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

int main(){ 
    //struct pollfd fds[3];
    struct fd_set fdset;
 

    // // 建立两个有名管道
    // if(access(FIFO1_PATH,F_OK)){
    //     printf("No FIFO1, create new one\n");
    //     mkfifo(FIFO1_PATH,0600|O_CREAT);
    // }
    // if(access(FIFO2_PATH,F_OK)){
    //     printf("No FIFO2, create new one\n");
    //     mkfifo(FIFO2_PATH,0600|O_CREAT);
    // }

    // fds[0].fd = open(FIFO1_PATH,O_RDONLY|O_NONBLOCK);
    // fds[1].fd = open(FIFO2_PATH,O_RDONLY|O_NONBLOCK);
    // fds[2].fd = 0; // open("/dev/stdin",O_RDONLY|O_NONBLOCK);


    // // 2s 超时
    // struct timeval delay_tv = {.tv_sec = 3};
    // int maxfdlen = MAX(MAX(fd[0],fd[1]),fd[2]);

    // 	int res;
	// char text[128];


#if 0
   // select()实现多IO复用，由轮询判断就绪条件
    while(FD_ISSET(fd[0],&fdset) || FD_ISSET(fd[1],&fdset) || FD_ISSET(fd[2],&fdset)){
        // 若fd[0:2]至少有一个就绪，（与运算短路），x=fd[1]
        tmp_fdset = fdset;
        // 为什么备份？,因为至少一个，触发轮询确定具体标号
        int res;
        res = select(maxfdlen+1,&tmp_fdset,NULL,NULL,&delay_tv);
        switch (res)
        {
            case -1:{

            }break;
            
            default:
                break;
        }
#endif

    // // 删除FIFO，以unlink解耦
    // unlink(FIFO1_PATH);
    // unlink(FIFO2_PATH);

    return 0;
}
