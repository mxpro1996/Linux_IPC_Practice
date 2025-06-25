#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <signal.h>

int main(int argc, char* argv[]){

	if(argc<2){
		printf("Usage: %s [pid] [signum]",argv[0]);
	}
	kill(atoi(argv[1]),atoi(argv[2]));

	return 0;
}

