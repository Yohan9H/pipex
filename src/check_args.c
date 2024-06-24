/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohurteb <yohurteb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 13:47:13 by yohurteb          #+#    #+#             */
/*   Updated: 2024/06/23 11:26:47 by yohurteb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	check_args(int argc, char **argv)
{
	int fd;

	if (argc < 5 || argc > 5)
	{
		write(2, "Invalid Argument\n", 17);
		exit(1);
	}
	if (access(argv[1], R_OK) == -1)
	{
		perror("zsh");
		exit(1);
	}
	fd = open(argv[4], O_RDONLY);
	if (fd == -1)
	{
		perror("zsh");
		exit(1);
	}
	close(fd);
}
