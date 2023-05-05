/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core_hex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antthoma <antthoma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 13:48:56 by antthoma          #+#    #+#             */
/*   Updated: 2023/02/21 00:32:50 by antthoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_get_pointer(va_list args, char c)
{
	int					length;
	char				*value;
	unsigned long int	data;

	data = va_arg(args, unsigned long int);
	if (!data)
	{
		length = ft_putstr("(nil)");
		return (length);
	}
	ft_putstr("0x");
	length = 2;
	value = ft_unsigned_to_hex(data, c);
	ft_putstr(value);
	length += ft_strlen(value);
	free(value);
	return (length);
}

int	ft_get_int(va_list args)
{
	int		length;
	char	*value;

	value = ft_itoa(va_arg(args, int));
	ft_putstr(value);
	length = ft_strlen(value);
	free(value);
	return (length);
}

int	ft_get_unsigned_to_ascii(va_list args)
{
	int		length;
	char	*value;

	value = ft_unsigned_to_ascii(va_arg(args, unsigned long));
	ft_putstr(value);
	length = ft_strlen(value);
	free(value);
	return (length);
}

int	ft_get_hex(va_list args, char c)
{
	int		length;
	char	*value;

	value = ft_unsigned_to_hex(va_arg(args, unsigned int), c);
	ft_putstr(value);
	length = ft_strlen(value);
	free(value);
	return (length);
}
