/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohurteb <yohurteb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 18:20:07 by yohan.h           #+#    #+#             */
/*   Updated: 2024/06/23 11:37:29 by yohurteb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

/*#include <string.h>
#include <stdio.h>
int	main()
{
	const char	s[] = " ";

	printf("My function   : %lu\n", ft_strlen(s));
	printf("Reel function : %zu\n", strlen(s));
	return (0);
}*/