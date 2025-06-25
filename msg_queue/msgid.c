#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <signal.h>
#include <sys/msg.h>
#include <sys/ipc.h>
#include <sys/sem.h>
// semaphor, not sys-signal
typedef struct{
	long mtype;
	char mtext[12];
}MSG_Type;

int main(){
	// 生成
	int msgid = msgget(ftok(".",114514),0600|IPC_CREAT);
	system("ipcs -q");
	printf("UUID: %u\n",msgid);
	MSG_Type msg;

	int pid = fork();
	if(pid==0){
		strcpy(msg.mtext,"Hello World");
		static int t=0;
		while(t<5){
			msg.mtype = getpid();
			printf("MType： %d\n",getpid());
			int ret = msgsnd(msgid,&msg,sizeof(msg.mtext),0);
			printf("Child: Sent msg type[2], %d\n",ret);
			sleep(1);
			t++;
		}memset(msg.mtext,0,12);
		// sent until OK
	}else if(pid>0){
			printf("MType： %d\n",pid);		
			wait(NULL);
		printf("BeforeRecv: ");
		puts(msg.mtext);
		do{
			puts("Wait start for msg[type=2]");
			sleep(1);
		}while(msgrcv(msgid,&msg,sizeof(msg.mtext),pid,IPC_NOWAIT)<=0);
		puts("Wait end for msg[type=2]");
		printf("Msg: ");
		puts(msg.mtext);
		kill(pid,SIGKILL);

		msgctl(msgid,IPC_RMID,NULL);
		system("ipcs -q") ;
	}


	return 0;
}

