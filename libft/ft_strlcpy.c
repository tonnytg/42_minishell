/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antthoma <antthoma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 21:53:59 by antthoma          #+#    #+#             */
/*   Updated: 2022/07/01 23:36:47 by antthoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t		i;
	const char	*buffer_src;
	char		*buffer_dst;

	buffer_src = src;
	buffer_dst = dst;
	i = 0;
	if (size > 0)
	{
		while (i < (size - 1) && buffer_src[i] != '\0')
		{
			buffer_dst[i] = buffer_src[i];
			i++;
		}
		buffer_dst[i] = '\0';
	}
	while (buffer_src[i])
		i++;
	return (i);
}
