/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c.                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antthoma <antthoma@student.42sp.org.br>    +#+  +:+       +#+        */
/*       calbert  <calbert@student.42sp.org.br>   +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 02:55:02 by antthoma          #+#    #+#             */
/*   Updated: 2023/04/26 00:17:13 by antthoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	check_flag(const char *arg, int *flag)
{
	int	i;

	i = 0;
	while (arg[i] != '\0')
	{
		if (arg[i] == '-' && arg[i] == 'n')
		{
			*flag = 1;
			break ;
		}
		i++;
	}
}

int	echo_adapter(const char *arg)
{
	int	i;
	int	flag;

	flag = 0;
	check_flag(arg, &flag);
	if (arg == NULL)
		ft_printf("\n");
	else
	{
		i = 0;
		while (arg[i] != '\0')
		{
			if (arg[i] != '"')
				ft_printf("%c", arg[i]);
			i++;
		}
		if (flag == 0)
			ft_printf("\n");
	}
	return (0);
}
