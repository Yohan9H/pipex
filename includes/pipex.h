/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohurteb <yohurteb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 13:24:12 by yohurteb          #+#    #+#             */
/*   Updated: 2024/06/27 13:13:21 by yohurteb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>

void	check_args(int argc, char **argv);

void	check_env(char **av, char **env, int pipefd[]);

char	**ft_split(char const *s, char c);

int		ft_printf(const char *format, ...)
		__attribute__((format(printf, 1, 2)));

int		nb_base_long(unsigned long nb, char *base, unsigned long size_b);

int		verif_nil(unsigned long nb, char *base, unsigned long size_b);

size_t	ft_strlen(const char *s);

char	*ft_strdup(const char *s1);

int		ft_strncmp(const char *s1, const char *s2, size_t n);

char	*ft_strjoin(const char *s1, const char *s2);

int		first_part(char **argv, char **env, int pipefd[]);

void	second_part(char **argv, char **env, int pipefd[], int pid);

void	fork_without_env(char **argv, char **cmd1, char **cmd2, int pipefd[]);

char 	*get_path(char **env);

void	free_split(char **tab);

void	free_all(char *path, char **cmd, char **path_split);

#endif