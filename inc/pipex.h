/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschmitt <aschmitt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 13:33:58 by aschmitt          #+#    #+#             */
/*   Updated: 2024/01/11 19:41:19 by aschmitt         ###   ########.fr       */
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
char	*ft_join(char *s1, char *s2);
char	**find_paths(char **envp);
void	free_tab(char **path);
void	error(char *s);
size_t	ft_strlen(char *s);
char	*ft_copy(char *cmd);

#endif