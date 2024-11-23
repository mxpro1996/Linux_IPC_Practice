#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <sys/stat.h>

#define FIFO_PATH	"/tmp/mytube"

int main(){
	int pid;
	char buf[32];
	int fd;

	if(access(FIFO_PATH,F_OK)<0){
		puts("No SuchFile");
		//fd = mkfifo(FIFO_PATH,O_WRONLY);
	}
	fd=open(FIFO_PATH,O_WRONLY);


	while(1){
		write(fd,"Hello",10);
		sleep(2);
	}


	return 0;
}

