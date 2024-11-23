#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/stat.h>
// 共享内存
#include <sys/shm.h>
// 信号量
#include <sys/sem.h>
#include <fcntl.h>
#include <signal.h>
#include <sys/select.h>
#include <sys/time.h>
char *shmaddr;
int semid,shmid;

// 二值信号量
void sem_init(int semid, int preval){
    // 此处的sem_num指代信号量索引
    semctl(semid,0,SETVAL,preval);
    // 初始化sem = 1
}

void sem_p(int semid){
    struct sembuf sop;
    // 支持批量操作
    sop.sem_num = 0; // only one
    sop.sem_op = -1;
    semop(semid,&sop,1);
}

void sem_v(int semid){
    struct sembuf sop;
    // 支持批量操作
    sop.sem_num = 0; // only one
    sop.sem_op = 1;
    semop(semid,&sop,1);
}

int sem_getval(int semid){
    // 此处的sem_num指代信号量索引
    return semctl(semid,0,GETVAL,NULL);
    // 初始化sem = 1
}

void signal_handler(int no){
    puts("Exit by Ctrl+C");
    shmdt(shmaddr);
    shmctl(shmid,IPC_RMID,NULL);
}

typedef struct{
    int authorid;
    int id;
    // 以textString作为产品
}GOOD_t;


int main(){
    // get-one
    signal(SIGINT,signal_handler);
    shmid = shmget(ftok(".",1),1,0600|IPC_CREAT);
    semid = semget(ftok(".",1),2,0600|IPC_CREAT);
    shmaddr = shmat(shmid,NULL,0);
    printf("Shmid: %d\n",shmid);

    sem_init(semid,1);
    // printf("Sem: %d\n", sem_getval(semid));
    // sem_p(semid);
    // printf("Sem: %d\n", sem_getval(semid));
    // sem_v(semid);
    // printf("Sem: %d\n", sem_getval(semid));
    // puts("")

    int cnt = 0;
    while(1){
        sem_p(semid);
        GOOD_t good = {.authorid = getpid(),.id=cnt};
        ++cnt;
        memcpy(shmaddr,&good,sizeof(good));
        printf("[%d] Create good(%d)\n",good.authorid,good.id);
        sem_v(semid);
        sleep(3);
    }

    return 0;
}