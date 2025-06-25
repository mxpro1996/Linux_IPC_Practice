#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

const char* buf ="HelloWorld";


int main(){
	pid_t pid = fork();
	if(pid>0){
		puts("Close DAD");
		while(1);
	}else if(pid==0){
		puts("KID Start");
		exit(0);
	}
	setsid();
	chdir("/tmp");
	umask(0);
	for(int i=0;i<getdtablesize();i++)
		close(i);

	int log_fd;
	while(1){
		log_fd = open("logd.txt",O_CREAT|O_WRONLY|O_APPEND);
		write(log_fd,buf,strlen(buf));
		close(log_fd);
		sleep(5);
	}
	exit(0);
}
