#include <unistd.h>
#include <sys/wait.h>
#include <sys/sem.h>
#include <stdio.h>
int semid;

void PV(int mode){
	struct sembuf sops = {
		.sem_num = 0,
		.sem_flg = SEM_UNDO,
		.sem_op = mode,
	};
	semop(semid,&sops,1);
}



int main(){
	int ret;
	int pipe1[2],pipe2[2];
	char dbuf[32];

	semid = semget(IPC_PRIVATE,1,0600|IPC_CREAT);
	PV(1);
	pipe(pipe1);
	pipe(pipe2);

	ret = fork();
	while(1){
		if(ret>0){
			// PV(-1);
			close(pipe1[0]);
			write(pipe1[1],"hello world",12);
			//PV(1);
			//usleep(20);
			//PV(-1);
			close(pipe2[1]);
			if(12==read(pipe2[0],dbuf,12)){
				printf("D-Recv: %.12s\n",dbuf);
			}
			//PV(1);
			
		}else if(ret==0){
			// PV(-1);
			close(pipe1[1]);
			if(12==read(pipe1[0],dbuf,12)){
				printf("C-Recv: %.12s\n",dbuf);
			}
			// PV(1);
			//usleep(20);
			//PV(-1);
			close(pipe2[0]);
			write(pipe2[1],"hello world",12);
			//PV(1);
		}
		usleep(500*1000);
	}
 
	return 0;
}
