/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calc_size_base.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antthoma <antthoma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 13:52:08 by antthoma          #+#    #+#             */
/*   Updated: 2022/09/26 13:52:15 by antthoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_calc_size_base(unsigned long int n, int base)
{
	int	i;

	if (!n)
		return (1);
	i = 0;
	while (n)
	{
		n = n / base;
		i++;
	}
	return (i);
}
