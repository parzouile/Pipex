/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschmitt <aschmitt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 16:39:52 by aschmitt          #+#    #+#             */
/*   Updated: 2023/12/18 16:44:31 by aschmitt         ###   ########.fr       */
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
