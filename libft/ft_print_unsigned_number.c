/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_unsigned_number.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antthoma <antthoma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 13:53:02 by antthoma          #+#    #+#             */
/*   Updated: 2022/09/26 13:53:03 by antthoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_print_unsig_numb(unsigned long nb)
{
	if (nb >= 10)
		ft_print_unsig_numb(nb / 10);
	ft_putchar_fd(nb % 10 + '0', 1);
}
