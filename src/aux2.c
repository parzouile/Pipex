/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschmitt <aschmitt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 16:39:52 by aschmitt          #+#    #+#             */
/*   Updated: 2024/02/19 10:14:05 by aschmitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*ft_copy(char *cmd)
{
	int		i;
	char	*bin;

	bin = malloc(sizeof(char) * ft_strlen(cmd) + 1);
	i = -1;
	while (cmd[++i])
		bin[i] = cmd[i];
	bin[i] = 0;
	return (bin);
}

char	*find_bin(char *cmd, char **envp, char **args)
{
	char	**path;
	char	*bin;
	int		i;

	i = 0;
	path = find_paths(envp, args);
	if (!path)
		ft_error("Malloc");
	while (path[i])
	{
		bin = ft_join(path[i], cmd);
		if (!bin)
			(free_tab(args), free_tab(path), ft_error("Malloc"));
		if (access(bin, F_OK) == 0)
		{
			free_tab(path);
			return (bin);
		}
		free(bin);
		i++;
	}
	free_tab(args);
	free_tab(path);
	ft_error("Command not found");
	return (NULL);
}
