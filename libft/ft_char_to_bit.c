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

char	*ft_char_to_bit(int dec)
{
	char	*bits;
	int		i;

	bits = malloc(sizeof(char) * 9);
	ft_bzero(bits, 9);
	i = 7;
	while (i >= 0)
	{
		if (dec % 2 == 0)
			bits[i] = '0';
		else
			bits[i] = '1';
		i--;
		dec = dec / 2;
	}
	return (bits);
}
