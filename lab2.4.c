#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

void childTask(){
	char name[10];
	printf("Enter name \n");
	fgets(name, 10, stdin);
	printf("Child name is %s\n", name);
	printf("Child process => PPID= %d, PID= %d\n\n", getppid(), getpid());
	
	exit(0);
}

void parentTask(){
	printf("Parent process => PID=%d\n", getpid());
	printf("All child processes have finished.\n");
	printf("Job is done\n");
}

void waitTask(){
	printf("Waiting for all child processes to finish...\n");
	wait(NULL);
	printf("Child process is done.\n");
	printf("********************\n");
}

int main(void){
	for(int i = 1; i < 5; i++) {
		pid_t pid = fork();
		if (pid == 0){
			childTask();
		}
		else if(i==4){
			waitTask();
			parentTask();
		}
		else{
			waitTask();
		}
	}
	return EXIT_SUCCESS;
}
