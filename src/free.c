/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohurteb <yohurteb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 10:31:56 by yohurteb          #+#    #+#             */
/*   Updated: 2024/06/28 10:55:04 by yohurteb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	exit_point(char **cmd)
{
	write(2, "error '.' is not valid\n", 23);
	free_split(cmd);
	exit(1);
}

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

void	free_all(char *path, char **cmd, char **path_split)
{
	int	i;

	i = 0;
	if (path)
		free(path);
	i = 0;
	if (cmd)
		free_split(cmd);
	i = 0;
	if (path_split)
		free_split(path_split);
}
