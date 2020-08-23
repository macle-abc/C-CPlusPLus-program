#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main()
{
	int pipefd[2] = { 0 };
	if (pipe(pipefd) == -1)
	{
		perror("pipe error!");
		exit(-1);
	}
	pid_t pid = fork();
	if (pid == -1)
	{
		perror("fork error!");
		exit(-1);
	}
	else if (pid == 0)
	{
		close(pipefd[0]);
		const char *message = "Child process 1 is sending a message!";
		if (write(pipefd[1], message, strlen(message)) != strlen(message))
		{
			perror("write error!");
		}
		close(pipefd[1]);
		exit(0);
	}
	else
	{
		pid = fork();
		if (pid == -1)
		{
			perror("second fork error!");
			exit(-1);
		}
		else if (pid == 0)
		{
			close(pipefd[0]);
			const char *message = "Child process 2 is sending a message!";
			if (write(pipefd[1], message, strlen(message)) != strlen(message))
			{
				perror("write error!");
			}
			close(pipefd[1]);
			exit(0);
		}
		else 
		{
			close(pipefd[1]);
			char buff[BUFSIZ] = { 0 };
			for (int i = 0; i != 2; ++i)
			{
				read(pipefd[0], buff, BUFSIZ);
				printf("%s\n", buff);
			}
			return 0;
		}
	}
}
