/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strategy_set_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caalbert <caalbert@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 02:55:02 by antthoma          #+#    #+#             */
/*   Updated: 2023/06/06 10:21:31 by caalbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	check_dless(t_cmds *cmds)
{
	if (ft_strcmp(cmds->current->type, "DLESS") == 0)
	{
		here_doc(cmds);
		if (cmds->current->next != NULL
			&& cmds->current->next->next != NULL
			&& ft_strcmp(cmds->current->next->next->type, "WORD") != 0)
			cmds->current->prev->strategy = S_SKIP_NEXT_FD;
		else
			if (cmds->current->prev != NULL)
				cmds->current->prev->strategy = S_DLESS_CURRENT;
		cmds->current->disabled = 1;
		if (cmds->current->next != NULL)
			cmds->current->next->disabled = 1;
	}
}

void	check_less(t_cmds *cmds)
{
	char		*msg;

	if (ft_strcmp(cmds->current->type, "LESS") == 0)
	{
		msg = read_from_file(cmds);
		if (!msg)
		{
			cmds->exit_code.code = 1;
			cmds->exit_code.msg = ft_strdup("No such file or directory");
			return ;
		}
		write_in_fd(cmds, msg);
		if (ft_strcmp(cmds->current->type, "WORD") != 0)
		{
			cmds->current->disabled = 1;
			cmds->current->next->disabled = 1;
		}
		cmds->current->prev->strategy = S_RECEIVER;
	}
}

void	check_pipe(t_cmds *cmds)
{
	if (ft_strcmp(cmds->current->type, "PIPE") == 0)
	{
		cmds->current->prev->strategy = S_PIPED;
		cmds->current->next->strategy = S_PIPED;
		cmds->current->disabled = 1;
	}
}
