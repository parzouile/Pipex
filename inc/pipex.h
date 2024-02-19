/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschmitt <aschmitt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 13:33:58 by aschmitt          #+#    #+#             */
/*   Updated: 2024/02/19 10:13:22 by aschmitt         ###   ########.fr       */
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
char	*find_bin(char *cmd, char **envp, char **args);
char	*ft_join(char *s1, char *s2);
char	**find_paths(char **envp, char **args);
void	free_tab(char **path);
void	ft_error(char *s);
size_t	ft_strlen(char *s);
char	*ft_copy(char *cmd);
void	command(char *cmd, char **envp);
void	processus(int new_pipe[2], int pipefd[2], char *cmd, char **envp);

#endif