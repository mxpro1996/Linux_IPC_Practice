#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int main(){
	int child1,child2,child;
	puts("Child1 created");
       	child1 = fork();
	if(child1==0){
		execlp("ls","ls",NULL);
		puts("Child1 exited");
		exit(0);
	}else if(child1>0){
		puts("Child2 created");
		child2 = fork();
		if(child2==0){
			sleep(3);
			puts("Child2 Exited");
		}else{
			// POLLING
			puts("Wait for Child1");
			waitpid(child1,NULL,0);
			puts("Wait end here1");

			do{
				child = waitpid(child2,NULL,WNOHANG);
				puts("Child2 still alive");
				sleep(1);
			}while(child!=child2);
			puts("Wait end here2");
		}

	}




	return 0;
}
