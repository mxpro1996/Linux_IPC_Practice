#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <signal.h>
#include <string.h>
#define MAX_SIZE 1e3+7


int main(){
	key_t key = ftok(".",1145);
	int shmid = shmget(key,MAX_SIZE,0666|IPC_CREAT);
	// Write + Read
	

	int pid = fork();
	if(pid>0){
		char *dad_ptr = NULL;
		dad_ptr = shmat(shmid,NULL,0);
		wait(NULL);
		puts(dad_ptr);	
		shmdt(dad_ptr);
	}else if(pid==0){
		char *kid_ptr = NULL;
		kid_ptr = shmat(shmid,NULL,0);
		strcpy(kid_ptr,"hell world");
		exit(0);
	}


	return 0;
}
