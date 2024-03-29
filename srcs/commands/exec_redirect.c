/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirect.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caalbert <caalbert@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 02:55:02 by antthoma          #+#    #+#             */
/*   Updated: 2023/06/06 10:21:31 by caalbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	exec_redirect(t_cmds *cmds)
{
	if (cmds->current->strategy == S_PIPED)
	{
		run_strategy(cmds);
	}
	else
	{
		create_fd_file(cmds);
		run_strategy(cmds);
		save_file(cmds);
		cmds->current->next->disabled = 1;
	}
}
