#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

int main() {
    // 创建一个信号量集
    key_t key = ftok(".", 'a');
    int semid = semget(key, 1, IPC_CREAT | 0666);
    if (semid == -1) {
        perror("semget");
        exit(1);
    }

    // 初始化信号量为 0
    union semun {
        int val;
        struct semid_ds *buf;
        unsigned short *array;
    } semun;
    semun.val = 0;
    if (semctl(semid, 0, SETVAL, semun) == -1) {
        perror("semctl (SETVAL)");
        exit(1);
    }

    // 打印初始信号量值
    struct semid_ds semnn;
    semctl(semid, 0, GETVAL, semnn);
    printf("初始信号量值: %d\n", semnn.val);

    // 模拟 P 操作
    struct sembuf sops;
    sops.sem_num = 0;
    sops.sem_op = -1;
    sops.sem_flg = SEM_UNDO;

    printf("执行 P 操作...\n");
    if (semop(semid, &sops, 1) == -1) {
        perror("semop (P)");
        exit(1);
    }

    // 打印信号量值
    semctl(semid, 0, GETVAL, semnn);
    printf("P 操作后信号量值: %d\n", semnn.val);

    // 模拟 V 操作
    sops.sem_op = 1;

    printf("执行 V 操作...\n");
    if (semop(semid, &sops, 1) == -1) {
        perror("semop (V)");
        exit(1);
    }

    // 打印信号量值
    semctl(semid, 0, GETVAL, semnn);
    printf("V 操作后信号量值: %d\n", semnn.val);

    // 删除信号量集
    if (semctl(semid, 0, IPC_RMID, semun) == -1) {
        perror("semctl (IPC_RMID)");
        exit(1);
    }

    printf("信号量集已删除\n");
    return 0;
}
