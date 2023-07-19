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

void	exec_builtin(t_cmds *cmds)
{
	find_command(cmds);
	if (cmds->cmd_finded->name)
	{
		cmds->exit_code.last_cmd = cmds->input->cmd_name;
		cmds->exit_code.code = cmds->cmd_finded->execute(cmds);
	}
	cmds->exit_code.last_cmd = cmds->input->cmd_name;
	cmds->exit_code.code = 0;
}

void	organize_commands(t_cmds *cmds)
{
	printf("organize commands: %p\n", cmds);
}

void	run_node(t_cmd_node *current)
{
	printf("current node: %p\n", current);
}

void	execute_cmd(t_cmds *cmds)
{
	t_cmd_node	*current;
	int			count;

	count = count_nodes(cmds);
	current = cmds->cmd_list;
	if (count == 1)
	{
		run_node(current);
	}
	else
	{
		while (current != NULL)
		{
			run_node(current);
			current = current->next;
		}
	}
	exec_builtin(cmds);
	organize_commands(cmds);
}
