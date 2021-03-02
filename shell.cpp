#include "shell.h"

void Shell::run()
{
	//while (true)
	{
		char* args[2] = { "ls", NULL };// "touch", "whoopty", NULL };
		pid_t pid = fork();
		switch (pid) 
		{
		case 0:
			execl("/bin/ls", "ls", NULL);
			perror("/bin/ls");
			exit(255);
		case -1:
			perror("fork");
			exit(1);
		default:
			int status;
			pid_t wait = waitpid(pid, &status, 0);
			if (wait < 0)
			{
				perror("wait");
				exit(254);
			}
		}
	}
}