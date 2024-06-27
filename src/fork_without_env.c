/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_without_env.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohurteb <yohurteb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 11:49:27 by yohurteb          #+#    #+#             */
/*   Updated: 2024/06/27 14:07:30 by yohurteb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	error_pid(void)
{
	perror("fork 2 failed");
	exit(1);
}

static	void	first_no_env(char **av, char **cmd1, char **cmd2, int pipe[])
{
	int	fd;

	fd = open(av[1], O_RDONLY);
	if (fd == -1)
		exit(1);
	dup2(fd, STDIN_FILENO);
	dup2(pipe[1], STDOUT_FILENO);
	close(pipe[1]);
	close(fd);
	execve(cmd1[0], cmd1, NULL);
	free_split(cmd1);
	free_split(cmd2);
	exit(1);
}

static	void	second_no_env(char **av, char **cmd1, char **cmd2, int pipe[])
{
	int	fd;

	fd = open(av[4], O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (fd == -1)
		exit(1);
	dup2(fd, STDOUT_FILENO);
	close(fd);
	close(pipe[1]);
	execve(cmd2[0], cmd2, NULL);
	free_split(cmd1);
	free_split(cmd2);
	exit(1);
}

void	fork_without_env(char **argv, char **cmd1, char **cmd2, int pipefd[])
{
	int	pid;

	pid = fork();
	if (pid == -1)
		error_pid();
	if (pid == 0)
		first_no_env(argv, cmd1, cmd2, pipefd);
	dup2(pipefd[0], STDIN_FILENO);
	pid = fork();
	if (pid == -1)
		error_pid();
	if (pid == 0)
		second_no_env(argv, cmd1, cmd2, pipefd);
	close(pipefd[0]);
	close(pipefd[1]);
	free_split(cmd1);
	free_split(cmd2);
	wait(NULL);
	wait(NULL);
	exit(0);
}
