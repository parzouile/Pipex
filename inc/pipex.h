/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschmitt <aschmitt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 13:33:58 by aschmitt          #+#    #+#             */
/*   Updated: 2023/12/18 16:44:43 by aschmitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdio.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>

char	**ft_split(char const *s, char c);
char	*find_bin(char *cmd, char **envp);
void	free_tab(char **path);
void	error(char *s);
size_t	ft_strlen(char *s);
char	*ft_copy(char *cmd);

#endif