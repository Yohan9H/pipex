/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohurteb <yohurteb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 13:47:13 by yohurteb          #+#    #+#             */
/*   Updated: 2024/06/27 13:46:57 by yohurteb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	excve_and_free(char **cmd, char **cmd_free)
{
	execve(cmd[0], cmd, NULL);
	free_split(cmd);
	free_split(cmd_free);
	exit(1);
}
void	check_no_env_but_path(char **env, char **argv, int pipefd[])
{
	char	**c1;
	char	**c2;

	c1 = ft_split(argv[2], ' ');
	if (!c1)
		exit(1);
	c2 = ft_split(argv[3], ' ');
	if (!c2)
	{
		free_split(c1);
		exit(1);
	}
	if (!*env && access(c1[0], X_OK) == -1  && access(c2[0], X_OK) == 0)
	{
		excve_and_free(c2, c1);
	}
	else if (!*env && access(c1[0], X_OK) == 0  && access(c2[0], X_OK) == -1)
	{
		excve_and_free(c1, c2);
	}
	else if (!*env && access(c1[0], X_OK) == 0  && access(c2[0], X_OK) == 0)
		fork_without_env(argv, c1, c2, pipefd);
	free_split(c1);
	free_split(c2);
}

void	check_env(char **av, char **env, int pipefd[])
{
	char	**cmd1;
	char	**cmd2;

	cmd1 = ft_split(av[2], ' ');
	if (!cmd1)
		exit(1);
	cmd2 = ft_split(av[3], ' ');
	if (!cmd2)
	{
		free_split(cmd1);
		exit(1);
	}
	if (!*env && access(cmd1[0], X_OK) == -1  && access(cmd2[0], X_OK) == -1)
	{
		write(2, "error command\n", 14);
		free_split(cmd1);
		free_split(cmd2);
		exit(1);
	}
	check_no_env_but_path(env, av, pipefd);
	free_split(cmd1);
	free_split(cmd2);
	return ;
}

void	check_args(int ac, char **av)
{
	int fd;

	if (ac < 5 || ac > 5)
	{
		write(2, "Invalid Argument\n", 17);
		exit(1);
	}
	if (av[2][0] == '\0' || av[3][0] == '\0')
	{
		write(2, "no command\n", 11);
		exit(1);
	}
	if (access(av[1], R_OK) == -1)
	{
		perror("not access infile");
		exit(1);
	}
	fd = open(av[4], O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (fd == -1)
	{
		perror("error outfile");
		exit(1);
	}
	close(fd);
}
