#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(){
	int pid,tube[2];
	char buf[32];

	pipe(tube);

	pid = fork();
	if(pid>0){
		close(tube[0]);
		// 关闭父读端
		sleep(2);
		write(tube[1],"114514",strlen(buf));
		close(tube[0]);
	}else if(pid==0){
		close(tube[1]);
		// 关闭子写端
		sleep(2);
		read(tube[0],buf,10);
		puts(buf);
	}


	return 0;
}

