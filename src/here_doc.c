/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschmitt <aschmitt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 14:25:29 by aschmitt          #+#    #+#             */
/*   Updated: 2024/02/19 15:40:28 by aschmitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	if (s1 == NULL || s2 == NULL)
		return (1);
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i ++;
	if (!s2[i] && s1[i] == '\n')
		return (0);
	return (s1[i] - s2[i]);
}

void	write_here_doc(char *limiter, int fd)
{
	char	*s;

	s = get_next_line(0);
	while (ft_strcmp(s, limiter) != 0)
	{
		write(fd, s, check_nl(s) + 1);
		if (s)
			free(s);
		s = get_next_line(0);
	}
	if (s)
		free(s);
	close(fd);
}

int	get_here_doc(char **argv)
{
	int	pipefd[2];

	if (ft_strcmp(argv[0], "here_doc") != 0)
		return (open(argv[0], O_RDONLY, 0644));
	if (pipe(pipefd) == -1)
		ft_error("Pipe");
	write_here_doc(argv[1], pipefd[1]);
	return (pipefd[0]);
}
