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
}

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>


int main(char *envp[])
{
	printEnvp(envp);
    pid_t pid;
    int fd;
    char *args[3];

    pid = fork();
    if (pid == -1)
    {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid == 0)
    {
        args[0] = "ls";
        args[1] = NULL;

        fd = open("test1.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
        dup2(fd, STDOUT_FILENO);
        close(fd);

        execve("/bin/ls", args, NULL);
    }
    else
    {
        wait(NULL);

        args[0] = "wc";
        args[1] = "-l";
        args[2] = NULL;

        fd = open("test1.txt", O_RDONLY);
        dup2(fd, STDIN_FILENO);
        close(fd);
        fd = open("test2.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
        dup2(fd, STDOUT_FILENO);
        close(fd);
        execve("/usr/bin/", args, NULL);
    }

    return 0;
}*/

#include <stdio.h>

void printEnvp(char *envp[]) {
    int i = 0;

    // Parcours du tableau envp jusqu'à ce que envp[i] soit NULL
    while (envp[i] != NULL) {
        printf("%s\n", envp[i]);
        i++;
    }
}

static char	*get_path_ptr(char *envp[])
{
	int		i;
	char	*ptr;

	i = 0;
	while (1)
	{
		ptr = envp[i];
		if (!ptr)
			break ;
		if (strncmp(ptr, "PATH=", 5) == 0)
			return (ptr);
		i++;
	}
	return (NULL);
}

char	*get_path(char *envp[])
{
	char	*path_ptr;
	char	**path;

	path_ptr = get_path_ptr(envp);
	path_ptr += 5;
	return (path);
}

int main(int argc, char **argv, char *envp[]) {
    // Appel de la fonction pour imprimer l'environnement
    printEnvp(envp);

    return 0;
}