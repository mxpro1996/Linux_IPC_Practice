#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <syslog.h>

const char* buf ="HelloWorld";


int main(){
	pid_t pid = fork();
	if(pid>0){
		puts("Close DAD");
		exit(0);
	}else if(pid==0){
		puts("KID Start");
	}
	setsid();
	chdir("/tmp");
	umask(0);
	for(int i=0;i<getdtablesize();i++)
		close(i);

	openlog("OhMyLOD",LOG_PID,LOG_DAEMON);
	int log_fd;
	//while(0);
	{	
		log_fd = open("logd.txt",O_WRONLY);
		if(log_fd<0){
			syslog(LOG_WARNING,"No SuchFile %s","114514");

		}
		write(log_fd,buf,strlen(buf));
		close(log_fd);
		sleep(5);
	}
	exit(0);
}


