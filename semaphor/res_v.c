#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <signal.h>

#include <sys/ipc.h>
#include <sys/sem.h>
// semaphor, not sys-signal



int main(){
	int semid = semget(IPC_PRIVATE,1,0600|IPC_CREAT);
	// req & create
	
	semctl(semid,0,SETVAL,0);
	// primary-value
	
	int pid = fork();
	if(pid==0){
		// delay 5s
		sleep(5);
		// V for 1
		struct sembuf sops;
		sops.sem_num = 0;
		sops.sem_op = 1;
		sops.sem_flg = SEM_UNDO;
		semop(semid,&sops,1);
	}else if(pid>0){
		struct sembuf sops;
		sops.sem_num = 0;
		sops.sem_flg = SEM_UNDO;
		// P for 1
		puts("Start wait");
		sops.sem_op = -1;
		semop(semid,&sops,1);
		puts("Wait end");
		printf("Decval: %hu\n",	semctl(semid,0,GETVAL,NULL));
		sops.sem_op = 1;
		semop(semid,&sops,1);
		printf("Decval: %hu\n",	semctl(semid,0,GETVAL,NULL));
		puts("Back +1");
		semctl(semid,1,IPC_RMID,NULL);
		puts("Remove signals");
		exit(0);
	}




	return 0;
}

