/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohurteb <yohurteb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 13:47:13 by yohurteb          #+#    #+#             */
/*   Updated: 2024/06/26 13:35:46 by yohurteb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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
