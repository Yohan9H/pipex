/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohurteb <yohurteb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 13:12:16 by yohurteb          #+#    #+#             */
/*   Updated: 2024/06/26 16:27:16 by yohurteb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*check_abs_path(char **cmd)
{
	char	*verif_path;

	verif_path = NULL;
	if (access(cmd[0], X_OK) == 0)
	{
		verif_path = ft_strdup(cmd[0]);
		if (!verif_path)
			return (NULL);
		return (verif_path);
	}
	return (verif_path);
}

char	*find_cmd(char **path, char **cmd)
{
	int		i;
	char	*verif_path;
	char	*tmp;

	i = 0;
	verif_path = check_abs_path(cmd);
	if (verif_path)
		return (verif_path);
	while (path[i])
	{
		if (verif_path)
			free(verif_path);
		verif_path = ft_strjoin(path[i++], "/");
		if (!verif_path)
			return (NULL);
		tmp = verif_path;
		verif_path = ft_strjoin(tmp, cmd[0]);
		free(tmp);
		if (!verif_path)
			return (NULL);
		if (access(verif_path, X_OK) == 0)
			return (verif_path);
	}
	free(verif_path);
	return (NULL);
}

char	*make_split(char **cmd, int pipefd[], char **env, char **path_split)
{
	char *path;

	close(pipefd[0]);
	path = get_path(env);
	path_split = ft_split(path, ':');
	if (!path_split)
		return (free_split(cmd), NULL);
	path = find_cmd(path_split, cmd);
	if (!path)
	{
		free_all(NULL, cmd, path_split);
		close(pipefd[1]);
		perror("command not found");
		exit(1);
	}
	return (path);
}

int	first_part(char **argv, char **env, int	pipefd[])
{
	char	**cmd1;
	char	**path_split;
	char	*path;
	int		fd;

	cmd1 = ft_split(argv[2], ' ');
	if (!cmd1)
		return (1);
	path_split = NULL;
	path = make_split(cmd1, pipefd, env, path_split);
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		return (free_all(path, cmd1, path_split), 1);
	dup2(fd, STDIN_FILENO);
	dup2(pipefd[1], STDOUT_FILENO);
	close(fd);
	close(pipefd[1]);
	execve(path, cmd1, env);
	free_all(path, cmd1, path_split);
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
		path_split = NULL;
		path = make_split(cmd2, pipefd, env, path_split);
		fd = open(argv[4], O_WRONLY | O_TRUNC | O_CREAT, 0644);
		if (fd == -1)
			return (free_all(path, cmd2, path_split));
		dup2(fd, STDOUT_FILENO);
		close(fd);
		close(pipefd[1]);
		execve(path, cmd2, env);
		free_all(path, cmd2, path_split);
		exit(1);
	}
}
