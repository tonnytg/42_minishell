/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antthoma <antthoma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 20:52:40 by antthoma          #+#    #+#             */
/*   Updated: 2022/07/13 23:02:22 by antthoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*pts;
	unsigned char	cc;

	pts = (void *)s;
	cc = c;
	i = 0;
	while (i < n)
	{
		if ((pts[i] - cc) == 0)
			return ((void *)pts + i);
		i++;
	}
	return (NULL);
}
