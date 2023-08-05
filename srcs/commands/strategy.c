/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strategy.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caalbert <caalbert@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 02:55:02 by antthoma          #+#    #+#             */
/*   Updated: 2023/06/06 10:21:31 by caalbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* Redirect output to file */
void	run_strategy(t_cmds *cmds)
{
	if (ft_strcmp(cmds->current->type, "WORD") == 0)
	{
		if (cmds->current->next)
		{
			dup2(cmds->current->fd_ptr_output[1], STDOUT_FILENO);
		}
	}
	else
		cmds->current->next->disabled = 1;
}

void	set_strategy(t_cmds *cmds)
{
	t_strategy	*s;

	s = ft_calloc(1, sizeof(t_strategy));
	cmds->strategy = 0;
	free(s);
	return ;
}
