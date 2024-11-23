#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <signal.h>
static void beforemain() __attribute__((constructor));
static void aftermain() __attribute__((destructor));

static void beforemain()
{
	puts("Run before _main entry");

}

static void aftermain(){
	puts("Run after _main return");
}

void signal_handler(int no){
	printf("Handler for signal %d\n",no);
	//exit(0);
}

int main(){
	struct sigaction action;
	sigaction(SIGINT,0,&action); // Get
	action.sa_handler = signal_handler;
	sigaction(SIGINT,&action,0); // Set

	//pause();
	while(1);


	return 0;
}

