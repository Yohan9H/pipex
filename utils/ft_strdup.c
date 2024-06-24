/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohurteb <yohurteb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 11:47:52 by yohan.h           #+#    #+#             */
/*   Updated: 2024/06/23 11:37:01 by yohurteb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*ft_strdup(const char *s1)
{
	char	*cpy;
	size_t	len_s1;
	size_t	i;

	i = 0;
	len_s1 = ft_strlen(s1);
	cpy = (char *)malloc((len_s1 + 1) * sizeof(char));
	if (!cpy)
		return (NULL);
	while (s1[i])
	{
		cpy[i] = s1[i];
		i++;
	}
	cpy[i] = '\0';
	return (cpy);
}

/*#include <string.h>
#include <stdio.h>
int	main()
{
	const char	str[] = "salut mon pote";
	char		*cpy;
	char		*cpy_r;


	printf("My function   : %s\n", cpy = ft_strdup(str));
	free(cpy);
	printf("Reel function : %s\n", cpy_r = strdup(str));
	free(cpy_r);

	return (0);
}*/