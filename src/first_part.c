/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_part.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohurteb <yohurteb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 13:12:16 by yohurteb          #+#    #+#             */
/*   Updated: 2024/06/24 17:30:38 by yohurteb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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

int	exec_cmd(int pipefd[], char **argv, char **cmd1, char **path_split)
{
	int	fd;

	close(pipefd[0]);
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
	{
		free_split(path_split);
		free_split(cmd1);
		return (1);
	}
	dup2(fd, STDIN_FILENO);
	dup2(pipefd[1], STDOUT_FILENO);
	//close(fd);
	return (0);
}

int	first_part(char **argv, char **env, int	pipefd[])
{
	char	**cmd1;
	char	**path_split;
	char	*path;

	cmd1 = ft_split(argv[2], ' ');
	if (!cmd1)
		return (1);
	path = get_path(env);
	path_split = ft_split(path, ':');
	if (!path_split)
		return (free_split(cmd1), 1);
	path = find_cmd(path_split, cmd1);
	if (exec_cmd(pipefd, argv, cmd1, path_split) == 1)
		return (1);
	execve(path, &cmd1[1], env);
	return (0);
}
