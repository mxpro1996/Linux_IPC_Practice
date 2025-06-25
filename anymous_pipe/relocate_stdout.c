#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>

int main() {
    int tube[2];
    pipe(tube);
    pid_t pid = fork();
    char buf[16];
    int sta;

    if (pid > 0) {
        close(tube[1]);
        sleep(2);

        // 使用循环读取数据，并打印到控制台
        //while (1) {
            if (read(tube[0], buf, 5) > 0) {
                printf("Parent received: %s\n", buf);
                //break;
            }
            sleep(1);
        //}

        exit(0);
    } else if (pid == 0) {
        close(tube[0]);
        sleep(2);

        // 重定向标准输出到管道
        if (dup2(tube[1], STDOUT_FILENO) == -1) {
            perror("dup2 error");
            exit(1);
        }

        // 打印信息到管道
        puts("KID Start and paused");
        exit(0); // 子进程退出
    }

    return 0;
}
