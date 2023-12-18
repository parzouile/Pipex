/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschmitt <aschmitt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 13:23:16 by aschmitt          #+#    #+#             */
/*   Updated: 2023/12/18 16:55:15 by aschmitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*args_path(char *args)
{
	int		i;
	int 	a;
	char	*s;

	i = -1;
	a = 0;
	while (args[++i])
	{
		if (args[i] == '/')
			a = i;
	}
	s = malloc(sizeof(char) * (i - a));
	if (!s)
		return (NULL);
	i = -1;
	while (args[++a])
		s[++i] = args[a];
	s[++i] = 0;
	free (args);
	return (s);
}

void	command(char *cmd, char **envp)
{
	char	**args;
	char	*bin;

	args = ft_split(cmd, ' ');
	if (!args)
		error("Error malloc\n");
	if (cmd[0] == '/')
	{
		bin = ft_copy(args[0]);
		args[0] = args_path(args[0]);
	}
	else 
		bin = find_bin(args[0], envp);
	if (!bin)
	{
		free_tab(args);
		error("Error Path\n");
	}
	if (execve(bin, args, envp) == -1)
		error("Error execution\n");
}

void	child_process(char **argv, int *pipefd, char **envp)
{
	int	fd;

	fd = open(argv[0], O_RDONLY, 0644);
	if (fd == -1)
		error("Error open\n");
	dup2(pipefd[1], STDOUT_FILENO);
	dup2(fd, STDIN_FILENO);
	close(pipefd[0]);
	command(argv[1], envp);
}

void	parent_process(char **argv, int *pipefd, char **envp)
{
	int	fd;

	fd = open(argv[3], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		error("Error open\n");
	dup2(fd, STDOUT_FILENO);
	dup2(pipefd[0], STDIN_FILENO);
	close(pipefd[1]);
	command(argv[2], envp);
}

int	main(int argc, char **argv, char **envp)
{
	pid_t	pid;
	int		pipefd[2];

	if (argc != 5)
		return (write(0, "Error args\n", 12));
	if (pipe(pipefd) == -1)
		return (write(0, "Error pipe\n", 12));
	pid = fork();
	if (pid == -1)
		return (write(0, "Error fork\n", 12));
	if (pid == 0)
		child_process(argv + 1, pipefd, envp);
	else
	{
		wait(NULL);
		parent_process(argv + 1, pipefd, envp);
	}
	return (0);
}
