/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caalbert <caalbert@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 02:55:02 by antthoma          #+#    #+#             */
/*   Updated: 2023/07/28 11:11:52 by caalbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	extract_input_values(t_cmds *cmds)
{
	char	*temp;

	temp = ft_strdup(cmds->input->datacpy);
	cmds->input->cmd_name = ft_strtok(temp, " ", 1);
	cmds->input->cmd_args = ft_strtok(NULL, "\0", 0);
	free(temp);
}

int	ft_isspace(int c)
{
	return (c == ' '
		|| c == '\t'
		|| c == '\n'
		|| c == '\r'
		|| c == '\v'
		|| c == '\f');
}

int	contains_only_spaces_or_tabs(const char *str)
{
	while (*str)
	{
		if (!ft_isspace(*str))
			return (0);
		str++;
	}
	return (1);
}

int	read_keyboard(t_cmds *cmds)
{
	load_signals();
	if (cmds->input->datacpy != NULL)
		free(cmds->input->datacpy);
	cmds->input->datacpy = readline("\033[0;32mminishell: > \033[0;0m");
	if (cmds->input->datacpy == NULL)
	{
		cmds->input->datacpy = ft_strdup("exit");
		cmds->signal_exit = 1;
		return (0);
	}
	if (contains_only_spaces_or_tabs(cmds->input->datacpy))
		return (1);
	add_history(cmds->input->datacpy);
	extract_input_values(cmds);
	if (check_quotes(cmds) == -1)
		return (1);
	return (0);
}
