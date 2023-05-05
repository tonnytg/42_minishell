/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antthoma <antthoma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 18:41:39 by antthoma          #+#    #+#             */
/*   Updated: 2022/07/01 23:34:36 by antthoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*mem;

	if ((nmemb * size) / size != nmemb)
		return (NULL);
	mem = malloc((nmemb * size));
	if (!mem)
		return (NULL);
	ft_memset(mem, '\0', (nmemb * size));
	return (mem);
}
