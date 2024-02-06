/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschmitt <aschmitt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 16:39:52 by aschmitt          #+#    #+#             */
/*   Updated: 2024/02/06 18:30:59 by aschmitt         ###   ########.fr       */
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

char	*find_bin(char *cmd, char **envp)
{
	char	**path;
	char	*bin;
	int		i;

	i = 0;
	path = find_paths(envp);
	if (!path)
		return (NULL);
	while (path[i])
	{
		bin = ft_join(path[i], cmd);
		if (access(bin, F_OK) == 0)
		{
			free_tab(path);
			return (bin);
		}
		free(bin);
		i++;
	}
	free_tab(path);
	return (NULL);
}
