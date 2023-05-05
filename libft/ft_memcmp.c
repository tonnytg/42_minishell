/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antthoma <antthoma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 11:15:51 by antthoma          #+#    #+#             */
/*   Updated: 2022/07/01 23:35:45 by antthoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		if (*(char *)s1 != *(char *)s2)
		{
			if (*(unsigned char *)s1 - *(unsigned char *)s2 > 0)
				return (1);
			if (*(unsigned char *)s1 - *(unsigned char *)s2 < 0)
				return (-1);
		}
		i++;
		s1++;
		s2++;
	}
	return (0);
}
