/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpreter.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caalbert <caalbert@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 02:55:02 by antthoma          #+#    #+#             */
/*   Updated: 2023/06/06 10:21:31 by caalbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_count_arr(char **arr)
{
	int	i;

	i = 0;
	while (arr[i] != NULL)
		i++;
	return (i);
}

void	ft_free_arr(char **arr)
{
	char	**ptr;

	if (arr == NULL)
		return ;
	ptr = arr;
	while (*ptr != NULL)
	{
		free(*ptr);
		ptr++;
	}
	free(arr);
}

void	parse_values_args(t_cmds *cmds)
{
	char	**original_args;
	char	**args_ptr;
	int		i;

	original_args = ft_split(cmds->current->phrase, ' ');
	cmds->current->phrase_parsed = ft_calloc(sizeof(char *),
			ft_count_arr(original_args) + 1);
	i = 0;
	args_ptr = original_args;
	while (*args_ptr != NULL)
	{
		if (strcmp(*args_ptr, "$PWD") == 0)
		{
			if (getenv("PWD") != NULL)
				cmds->current->phrase_parsed[i] = ft_strdup(getenv("PWD"));
		}
		else if (strcmp(*args_ptr, "$?") == 0)
			cmds->current->phrase_parsed[i] = ft_itoa(cmds->exit_code.code);
		else
			cmds->current->phrase_parsed[i] = ft_strdup(*args_ptr);
		args_ptr++;
		i++;
	}
	ft_free_arr(original_args);
}

void	init_interpreter(t_cmds *cmds)
{
	parse_values_args(cmds);
}
