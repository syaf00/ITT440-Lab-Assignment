#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <errno.h>
#include <signal.h>

void sigint_handler(int sig)
{
	printf("Process terminated.\n");
}

int main(void){
	int pipefds[2];
	int num;
	int j;
	int flag= 0;

	if (pipe(pipefds)== -1)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}

	pid_t pid= fork();
	if (pid == 0)
	{
		void sigint_handler(int sig);
		if (signal(SIGINT, sigint_handler)== SIG_ERR)
		{
			perror("signal");
			exit(1);
		}
		
		printf("Enter a number: ");
		scanf("%d", &num);
		
		close(pipefds[0]);
		write(pipefds[1], &num, sizeof(num));
		exit(EXIT_SUCCESS);
	}
	
	if (pid > 0)
	{
		wait(NULL);
		close(pipefds[1]);
		read(pipefds[0], &num, sizeof(num));

		for (j= 2; j <= num/2; j++)
		{
			if (num % j == 0)
			{
				flag= 1;
				break;
			}
		}
			
		if (num == 1)
		{
			printf("1 is not categorized as a prime number\n");
		}
		else
		{
			if (flag == 0)
				printf("%d is a prime number\n", num);
			else
			printf("%d is not a prime number\n", num);
		}
		
		close(pipefds[0]);
	}
	return EXIT_SUCCESS;
}
