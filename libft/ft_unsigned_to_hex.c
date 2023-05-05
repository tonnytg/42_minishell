/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unsigned_to_hex.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antthoma <antthoma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 13:53:47 by antthoma          #+#    #+#             */
/*   Updated: 2022/09/26 13:53:51 by antthoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_unsigned_to_hex(unsigned long long n, char flag)
{
	char	*str;
	char	base;
	size_t	size;

	if (n == 0)
		return (ft_strdup("0"));
	size = ft_calc_size_base(n, 16);
	if (flag == 'X')
		base = 'A';
	else
		base = 'a';
	str = malloc((size + 1) * sizeof(char));
	if (!str)
		return (NULL);
	str[size] = '\0';
	while (size > 0)
	{
		if (n % 16 > 9)
			str[size - 1] = (n % 16) + base - 10;
		else
			str[size - 1] = (n % 16) + '0';
		n = n / 16;
		size--;
	}
	return (str);
}
