/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caalbert <caalbert@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 02:55:02 by antthoma          #+#    #+#             */
/*   Updated: 2023/06/06 10:21:31 by caalbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	open_pipe(t_cmd_node *current)
{
	printf("open pipe fd in node %p\n", current);
	if (pipe(current->fd) < 0)
		exit (write (1, "Pipe error\n", 12));
}

void	load_commands(t_cmds *cmds)
{
	cmds->current->cmd_name = ft_strtok(cmds->current->phrase_temp, " ", 1);
	cmds->current->full_args = ft_strtok(NULL, "", 0);
}

void	execute_cmd(t_cmds *cmds)
{
	cmds->current = cmds->cmd_list;
	while (cmds->current != NULL)
	{
		run_node(cmds);
		cmds->current = cmds->current->next;
	}
}
