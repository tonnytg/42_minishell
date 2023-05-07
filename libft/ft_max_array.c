/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_max.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antthoma <antthoma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 13:23:45 by antthoma          #+#    #+#             */
/*   Updated: 2023/03/10 03:11:08 by antthoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	max_arrary(int *arr, int len)
{
	int	i;
	int	max_val;

	i = 1;
	max_val = arr[0];
	while (i < len)
	{
		if (arr[i] > max_val)
		{
			max_val = arr[i];
		}
		i++;
	}
	return (max_val);
}
