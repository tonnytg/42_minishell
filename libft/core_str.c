/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core_str.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antthoma <antthoma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 13:48:56 by antthoma          #+#    #+#             */
/*   Updated: 2023/02/21 00:32:54 by antthoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_get_char(va_list args)
{
	int	length;

	length = 0;
	length += ft_putchar_fd(va_arg(args, int), 1);
	return (length);
}

int	ft_get_str(va_list args)
{
	int		length;
	char	*text;

	text = va_arg(args, char *);
	if (!text)
		length = ft_putstr("(null)");
	else
		length = ft_putstr(text);
	return (length);
}
