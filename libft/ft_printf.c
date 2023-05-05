/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antthoma <antthoma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 13:47:13 by antthoma          #+#    #+#             */
/*   Updated: 2023/02/21 00:32:07 by antthoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_choice(char c, int length, va_list args)
{
	if (c == 'c')
		length += ft_get_char(args);
	else if (c == 's')
		length += ft_get_str (args);
	else if (c == 'p')
		length += ft_get_pointer (args, c);
	else if (c == 'd' || c == 'i')
		length += ft_get_int(args);
	else if (c == 'u')
		length += ft_get_unsigned_to_ascii(args);
	else if (c == 'x' || c == 'X')
		length += ft_get_hex(args, c);
	else if (c == '%')
		length += write(1, &c, 1);
	return (length);
}

int	ft_printf(const char *str, ...)
{
	int		i;
	int		length;
	va_list	args;

	va_start(args, str);
	i = 0;
	length = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '%')
		{
			i++;
			length = ft_choice(str[i], length, args);
		}
		else
			length += ft_putchar_fd(str[i], 1);
		i++;
	}
	va_end(args);
	return (length);
}
