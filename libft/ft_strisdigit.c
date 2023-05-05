/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strisdigit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antthoma <antthoma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 23:31:58 by antthoma          #+#    #+#             */
/*   Updated: 2023/02/17 13:52:36 by antthoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strisdigit(char *str)
{
	int	n;

	n = 0;
	while (str[n])
	{
		if (ft_isdigit(str[n]) <= 0)
			return (0);
		n++;
	}
	return (1);
}
