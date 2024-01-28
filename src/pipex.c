/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschmitt <aschmitt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 13:23:16 by aschmitt          #+#    #+#             */
/*   Updated: 2024/01/28 13:47:12 by aschmitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*args_path(char *args)
{
	int		i;
	int		a;
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
		ft_error("Error malloc\n");
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
		ft_error("Error Path\n");
	}
	if (execve(bin, args, envp) == -1)
		ft_error("Error execution\n");
}

void	child_process(char **argv, int *pipefd, char **envp)
{
	int	fd;

	fd = open(argv[0], O_RDONLY, 0644);
	if (fd == -1)
		ft_error("Error open\n");
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
		ft_error("Error open\n");
	dup2(fd, STDOUT_FILENO);
	dup2(pipefd[0], STDIN_FILENO);
	close(pipefd[1]);
	command(argv[2], envp);
}

int	first_process(char **argv, int pipefd[2], char **envp)
{
	int		fd;
	pid_t	pid;

	fd = open(argv[0], O_RDONLY, 0644);
	if (fd == -1)
		ft_error("Error open\n");
	pid = fork();
	if (pid == -1)
	{
		close(fd);
		close(pipefd[0]);
		close(pipefd[1]);
		ft_error("pipex: fork");
	}
	else if (pid == 0)
	{
		dup2(pipefd[1], STDOUT_FILENO);
		dup2(fd, STDIN_FILENO);
		close(pipefd[0]);
		command(argv[1], envp);
	}
	return (1);
}

int	mid_process(int pipefd[2], char *cmd, char **envp)
{
	pid_t	pid;
	int		new_pipe[2];

	close(pipefd[1]);
	if (pipe(new_pipe) == -1)
	{
		(write(2, "Error pipe\n", 12));
	}
	pid = fork();
	if (pid == -1)
	{
		close(pipefd[0]);
		close(new_pipe[0]);
		close(new_pipe[1]);
		ft_error("pipex: fork");
	}
	else if (pid == 0)
	{
		dup2(new_pipe[1], STDOUT_FILENO);
		dup2(pipefd[0], STDIN_FILENO);
		close(new_pipe[0]);
		command(cmd, envp);
		close(pipefd[0]);
		close(new_pipe[1]);
	}
	else
	{
		pipefd[0] = new_pipe[0];
		pipefd[1] = new_pipe[1];
	}
	return (1);
}

int	last_process(char **argv, int pipefd[2], char **envp, int i)
{
	pid_t	pid;
	int		fd;

	fd = open(argv[i + 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		ft_error("Error open\n");
	close(pipefd[1]);
	pid = fork();
	if (pid == -1)
	{
		close(pipefd[0]);
		close(pipefd[1]);
		ft_error("pipex: fork");
	}
	else if (pid == 0)
	{
		dup2(pipefd[0], STDIN_FILENO);
		dup2(fd, STDOUT_FILENO);
		command(argv[i], envp);
		close(pipefd[0]);
		exit(1);
	}
	else
	{
		close(pipefd[0]);
	}
	return (1);
}


void	pipex(int argc, char **argv, char **envp, int pipefd[2])
{
	int	i;

	i = 1;
	if (!first_process(argv, pipefd, envp))
		return ;
	while (++i < argc - 2)
	{
		
		mid_process(pipefd, argv[i], envp);
	}
	last_process(argv, pipefd, envp, i);
	
}

int	main(int argc, char **argv, char **envp)
{
	int		pipefd[2];

	if (argc < 5)
		return (write(2, "Error args\n", 12));
	if (pipe(pipefd) == -1)
		return (write(2, "Error pipe\n", 12));
	pipex(argc - 1, argv + 1, envp, pipefd);
	return (0);
}
