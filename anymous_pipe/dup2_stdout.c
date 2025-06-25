#include<stdio.h>
#include <sys/wait.h>
#include<unistd.h>
#include<string.h>
#include<stdlib.h>
int main()
{
	int fpipe[2] = {0};
	pid_t fpid;
	char massage[1000] = {0};
	memset(massage, 0, 20);
	if (pipe(fpipe) < 0)
	{
		printf("Create pipe error!\n");
	}
	fpid = fork();
	if (fpid == 0)
	{
		//close(fpipe[0]);
		dup2(fpipe[1],STDOUT_FILENO);
		execlp("uname","uname","-a",NULL);
	}
	else if (fpid > 0)
	{
		wait(NULL);
		printf("RECV:");
		//fflush(stdout);
		//close(fpipe[1]);
		read(fpipe[0], massage, 1000);
		printf("%s\n",massage);
	}
	else
	{
		printf("create fork error!\n");
	}
	return 0;
}
