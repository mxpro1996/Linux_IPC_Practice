#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <syslog.h>
#include <signal.h>
#include <stdint.h>

//const char* buf ="HelloWorld";
void msleep(uint32_t xms){
	usleep(xms*1000);
}


int main(){
	int tube[2];
	pipe(tube);
	char buf[16];
	int sta;
	pid_t pid = fork();

	if(pid>0){
		close(tube[1]);
		int ret;
		dup2(tube[0],STDIN_FILENO);
		char s[16];
		while(1){
			scanf("%s",s);
			puts(s);
		}
	}else if(pid==0){
		close(tube[0]);
		sleep(2);
		dup2(tube[1],STDOUT_FILENO);
		while(1){
			printf("KID: SayHello");
			fflush(stdout);
			msleep(500);
		}
	}

	exit(0);
}


