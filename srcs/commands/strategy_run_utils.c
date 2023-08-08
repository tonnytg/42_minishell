/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strategy_run_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antthoma <caalbert@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 02:55:02 by antthoma          #+#    #+#             */
/*   Updated: 2023/06/06 10:21:31 by caalbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	run_strategy_piped(t_cmds *cmds)
{
	if (cmds->current->strategy == S_PIPED)
	{
		if (ft_strcmp(cmds->current->type, "WORD") == 0)
		{
			if (cmds->current->prev == NULL && cmds->current->next != NULL)
			{
				dup2(cmds->current->fd_ptr_output[1], STDOUT_FILENO);
				close(cmds->current->fd_ptr_output[0]);
			}
			else if (cmds->current->prev != NULL && cmds->current->next != NULL)
			{
				dup2(cmds->current->fd_ptr_input[0], STDIN_FILENO);
				close(cmds->current->fd_ptr_input[0]);
				dup2(cmds->current->fd_ptr_output[1], STDOUT_FILENO);
				close(cmds->current->fd_ptr_output[1]);
			}
			else if (cmds->current->prev != NULL && cmds->current->next == NULL)
			{
				dup2(cmds->current->fd_ptr_input[0], STDIN_FILENO);
				close(cmds->current->fd_ptr_input[0]);
			}
		}
	}
}
