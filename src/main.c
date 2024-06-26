/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohurteb <yohurteb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 14:47:18 by yohurteb          #+#    #+#             */
/*   Updated: 2024/06/26 10:32:06 by yohurteb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char *get_path(char **env)
{
	size_t	j;

	j = 0;
	while (env[j])
	{
		if (ft_strncmp(env[j], "PATH=", 5) == 0)
			return (&env[j][5]);
		j++;
	}
	return (NULL);
}

int	main(int argc, char **argv, char **env)
{
	int		pipefd[2];
	pid_t	pid;

	(void)argc;
	check_args(argc, argv);
	if (pipe(pipefd) == -1)
		return (perror("error pipe"), 1);
	pid = fork();
	if (pid == -1)
		return (perror("fork failed"), 1);
	if (pid == 0)
	{
		if (first_part(argv, env, pipefd) == 1)
			return (1);
	}
	dup2(pipefd[0], STDIN_FILENO);
	pid = fork();
	if (pid == -1)
		return (perror("fork 2 failed"), 1);
	second_part(argv, env, pipefd, pid);
	close(pipefd[0]);
	close(pipefd[1]);
	wait(NULL);
	wait(NULL);
}
