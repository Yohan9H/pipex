/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_part.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohurteb <yohurteb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 13:12:16 by yohurteb          #+#    #+#             */
/*   Updated: 2024/06/25 16:03:45 by yohurteb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_path_and_cmd(char **path, char **cmd)
{
	int	i;

	i = 0;
	while (path[i])
		free(path[i++]);
	free(path);
	path = NULL;
	i = 0;
	while (cmd[i])
		free(cmd[i++]);
	free(cmd);
	cmd = NULL;
}

char	*find_cmd(char **path, char **cmd)
{
	int		i;
	char	*verif_path;

	i = 0;
	while (path[i])
	{
		verif_path = ft_strjoin(path[i], "/");
		verif_path = ft_strjoin(verif_path, cmd[0]);
		if (access(verif_path, X_OK) == 0)
			return (verif_path);
		i++;
	}
	return (NULL);
}

int	first_part(char **argv, char **env, int	pipefd[])
{
	char	**cmd1;
	char	**path_split;
	char	*path;
	int		fd;

	close(pipefd[0]);
	cmd1 = ft_split(argv[2], ' ');
	if (!cmd1)
		return (1);
	path = get_path(env);
	path_split = ft_split(path, ':');
	if (!path_split)
		return (free_split(cmd1), 1);
	path = find_cmd(path_split, cmd1);
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		return (free_path_and_cmd(path_split, cmd1), 1);
	dup2(fd, STDIN_FILENO);
	dup2(pipefd[1], STDOUT_FILENO);
	close(fd);
	close(pipefd[1]);
	execve(path, cmd1, env);
	return (0);
}

void	second_part(char **argv, char **env, int pipefd[], int pid)
{
	char	**cmd2;
	char	**path_split;
	char	*path;
	int		fd;

	if (pid == 0)
	{
		cmd2 = ft_split(argv[3], ' ');
		if (!cmd2)
			exit(1);
		path = get_path(env);
		path_split = ft_split(path, ':');
		if (!path_split)
			return (free_split(cmd2));
		path = find_cmd(path_split, cmd2);
		fd = open(argv[4], O_WRONLY | O_TRUNC | O_CREAT, 0644);
		if (fd == -1)
			return (free_path_and_cmd(path_split, cmd2));
		dup2(fd, STDOUT_FILENO);
		close(fd);
		close(pipefd[1]);
		execve(path, cmd2, env);
		exit(1);
	}
}
