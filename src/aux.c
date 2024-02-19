/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschmitt <aschmitt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 17:36:40 by aschmitt          #+#    #+#             */
/*   Updated: 2024/02/19 10:13:34 by aschmitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**find_paths(char **envp, char **args)
{
	int		i;
	int		a;
	char	*s;

	i = -1;
	s = "PATH=";
	while (envp[++i])
	{
		a = 0;
		while (envp[i][a] && s[a] && envp[i][a] == s[a])
			a ++;
		if (a == 5)
			break ;
	}
	if (a == 5)
		return (ft_split(envp[i] + 5, ':'));
	free_tab(args);
	write(2, "Error Path\n", 12);
	exit(1);
	return (NULL);
}

size_t	ft_strlen(char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i ++;
	return (i);
}

void	free_tab(char **path)
{
	int	i;

	i = -1;
	while (path[++i])
		free(path[i]);
	free(path);
}

char	*ft_join(char *s1, char *s2)
{
	char	*result;
	size_t	i;
	size_t	j;

	if (!s1 || !s2)
		return (NULL);
	result = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 2));
	if (!result)
		return (NULL);
	i = -1;
	while (s1[++i])
		result[i] = s1[i];
	result[i++] = '/';
	j = -1;
	while (s2[++j])
		result[i + j] = s2[j];
	result[i + j] = '\0';
	return (result);
}

void	ft_error(char *s)
{
	perror(s);
	exit(1);
}
