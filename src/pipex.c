/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschmitt <aschmitt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 13:23:16 by aschmitt          #+#    #+#             */
/*   Updated: 2024/02/07 12:34:08 by aschmitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	first_process(char **argv, int pipefd[2], char **envp)
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
	wait(&pid);
}

void	mid_process(int pipefd[2], char *cmd, char **envp)
{
	pid_t	pid;
	int		new_pipe[2];

	close(pipefd[1]);
	if (pipe(new_pipe) == -1)
		(close(pipefd[0]), ft_error("Error pipe\n"));
	pid = fork();
	if (pid == -1)
	{
		close(pipefd[0]);
		close(new_pipe[0]);
		close(new_pipe[1]);
		ft_error("pipex: fork");
	}
	else if (pid == 0)
		processus(new_pipe, pipefd, cmd, envp);
	wait(&pid);
	pipefd[0] = new_pipe[0];
	pipefd[1] = new_pipe[1];
}

void	last_process(char **argv, int pipefd[2], char **envp, int i)
{
	pid_t	pid;
	int		fd;

	close(pipefd[1]);
	fd = open(argv[i + 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		(close(pipefd[0]), ft_error("Error open\n"));
	pid = fork();
	if (pid == -1)
		(close(pipefd[0]), ft_error("pipex: fork"));
	else if (pid == 0)
	{
		dup2(pipefd[0], STDIN_FILENO);
		dup2(fd, STDOUT_FILENO);
		command(argv[i], envp);
		(close(pipefd[0]), ft_error("Error  command execution\n"));
	}
	wait(&pid);
	close(pipefd[0]);
}

void	pipex(int argc, char **argv, char **envp)
{
	int	pipefd[2];
	int	i;

	i = 1;
	if (pipe(pipefd) == -1)
		ft_error("Error pipe\n");
	first_process(argv, pipefd, envp);
	while (++i < argc - 2)
		mid_process(pipefd, argv[i], envp);
	last_process(argv, pipefd, envp, i);
}

int	main(int argc, char **argv, char **envp)
{
	if (argc < 5)
		return (write(2, "Error args\n", 12));
	pipex(argc - 1, argv + 1, envp);
	return (0);
}
