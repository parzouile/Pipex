#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
 
#include <stdio.h>
#include <unistd.h>
 
/*int main()
{
	int	fd;
	char *args[3];

	if (access("example.txt", W_OK) != -1)
	{
		fd = open("example.txt", O_WRONLY | O_CREAT, 0644);
		dup2(fd, STDOUT_FILENO);
		close(fd);
		printf("I have permission\n");
	}
	else
		printf("I don't have permission\n");
 

	
 
	args[0] = "mkdir";
	args[1] = "tt";
	args[2] = NULL;
	execve("/bin/mkdir", args, NULL);
	printf("This line will not be executed.\n");

	
 
	return (0);
}*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
 
int main()
{
	pid_t pid;
 
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
 
	if (pid == 0)
		printf("This is the child process. (pid: %d)\n", getpid());
	else
		printf("This is the parent process. (pid: %d)\n", getpid());
	printf(" (pid: %d)\n", getpid());
	return (0);
}
