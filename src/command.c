/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschmitt <aschmitt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 17:48:02 by aschmitt          #+#    #+#             */
/*   Updated: 2024/02/06 18:46:05 by aschmitt         ###   ########.fr       */
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

void	processus(int new_pipe[2], int pipefd[2], char *cmd, char **envp)
{
	dup2(new_pipe[1], STDOUT_FILENO);
	dup2(pipefd[0], STDIN_FILENO);
	close(new_pipe[0]);
	command(cmd, envp);
	close(pipefd[0]);
	close(new_pipe[1]);
	ft_error("Error\n");
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
