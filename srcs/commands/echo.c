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

void	free_args(char **args)
{
	int	i;

	i = 0;
	while (args[i] != NULL)
	{
		free(args[i]);
		i++;
	}
	free(args);
}

void	print_args(char **args)
{
	int	i;

	i = 0;
	while (args[i] != NULL)
	{
		ft_printf("%s ", args[i]);
		i++;
	}
}

int	echo_adapter(const char *args)
{
	char	**words;
	int		i;
	int		trigger;

	trigger = 0;
	words = ft_split(args, ' ');
	if (words == NULL)
	{
		ft_printf("\n");
		return (0);
	}
	i = 0;
	if (ft_strcmp(words[0], "-n") == 0)
	{
		i = 1;
		trigger = 1;
	}
	print_args(words + i);
	if (trigger == 0)
		ft_printf("\n");
	free_args(words);
	return (0);
}
