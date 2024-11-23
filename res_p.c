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
union{
	int val;
	struct semid_ds *buf;
	unsigned short *array;
}semnn;


int main(){
	int semid = semget(ftok(".",114514),1,0600|IPC_CREAT);
	// req & create
	
	semnn.val = 0; // default 0
	semctl(semid,1,SETVAL,semnn);
	
	// primary-value
	
	//int pid = fork();
	//if(pid==0){
		// delay 5s
		//sleep(5);
		// V for 1
		struct sembuf sops;
		sops.sem_num = 0;
		sops.sem_op = -1;
		sops.sem_flg = SEM_UNDO;
		puts("Try get x1");
		semop(semid,&sops,1);
		puts("Producted -1");
	//}



	return 0;
}

