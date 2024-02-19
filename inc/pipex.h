/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschmitt <aschmitt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 13:33:58 by aschmitt          #+#    #+#             */
/*   Updated: 2024/02/19 15:45:30 by aschmitt         ###   ########.fr       */
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

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 20
# endif

char	*get_next_line(int fd);
size_t	ft_strlen(char *s);
int		check_nl(char *stack);
char	*add_to_stack(char *stack, char *buff);
char	*ft_new_stack(char *buff);
char	*get_next_line(int fd);

char	**ft_split(char const *s, char c);
char	*find_bin(char *cmd, char **envp, char **args);
char	*ft_join(char *s1, char *s2);
char	**find_paths(char **envp, char **args);
void	free_tab(char **path);
void	ft_error(char *s);
char	*ft_copy(char *cmd);
void	command(char *cmd, char **envp);
void	processus(int new_pipe[2], int pipefd[2], char *cmd, char **envp);
int		ft_strcmp(char *s1, char *s2);
int		get_here_doc(char **argv);

#endif