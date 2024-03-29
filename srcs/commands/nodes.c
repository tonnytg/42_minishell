/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nodes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caalbert <caalbert@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 02:55:02 by antthoma          #+#    #+#             */
/*   Updated: 2023/06/06 10:21:31 by caalbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_current_cmds(t_cmds *cmds)
{
	free(cmds->current->cmd_name);
	free(cmds->current->full_args);
	free_arr(cmds->current->phrase_parsed);
	if (cmds->current->phrase != NULL)
	{
		free(cmds->current->phrase);
		cmds->current->phrase = NULL;
	}
}

int	count_nodes(t_cmds *cmds)
{
	t_cmd_node	*current;
	int			count;

	count = 0;
	current = cmds->cmd_list;
	while (current != NULL)
	{
		count++;
		current = current->next;
	}
	cmds->cmds_list_count = count;
	return (count);
}

void	run_commands(t_cmds *cmds)
{
	int	type_command;

	type_command = -1;
	init_interpreter(cmds);
	type_command = check_type_command(cmds);
	if (type_command == 0)
		exec_builtin(cmds);
	else if (type_command == 1)
		exec_external(cmds);
	else
	{
		printf("minishell: %s: command not found\n",
			cmds->current->cmd_name);
		cmds->exit_code.code = 127;
	}
	free_current_cmds(cmds);
}

void	run_node(t_cmds *cmds)
{
	if (cmds->current->disabled == 0)
	{
		if (ft_strcmp(cmds->current->type, "WORD") == 0)
		{
			run_commands(cmds);
		}
		else
		{
			exec_redirect(cmds);
		}
	}
	else
		return ;
}
