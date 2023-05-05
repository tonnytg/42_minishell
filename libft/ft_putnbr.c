/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antthoma <antthoma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 13:53:15 by antthoma          #+#    #+#             */
/*   Updated: 2022/09/26 13:54:11 by antthoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putnbr(int nb)
{
	int	length;

	length = 0;
	if (nb < 0)
	{
		length += ft_putchar_fd('-', 1);
		nb = -nb;
	}
	if (nb >= 10)
	{
		length += ft_putnbr(nb / 10);
	}
	length += ft_putchar_fd(nb % 10 + '0', 1);
	return (length);
}
