/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohurteb <yohurteb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 14:47:18 by yohurteb          #+#    #+#             */
/*   Updated: 2024/06/24 16:28:24 by yohurteb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_split(char **tab)
{
	int	i;

	i = 0;
	if (!tab)
		return ;
	while (tab[i])
		free(tab[i++]);
	free(tab);
	tab = NULL;
}

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
	//check_args(argc, argv);
	pid = fork();
	if (pid == -1)
		return (perror("zsh"), 1);
	if (pipe(pipefd) == -1)
		return (perror("error pipe"), 1);
	if (pid == 0)
	{
		if (first_part(argv, env, pipefd) == 1)
			return (1);
	}
	char	buffer[1024];
	wait(NULL);
	close(pipefd[1]);
	read(pipefd[0], buffer, 1024);
	printf("%s", buffer);
}
