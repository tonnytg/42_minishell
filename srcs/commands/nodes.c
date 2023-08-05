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

void exec_redirect(t_cmds *cmds)
{
	run_strategy(cmds);
	printf("[exec_redirect] - Sou um REDIRECT agora!----!\n");
	if (ft_strcmp(cmds->current->type, "GREAT") == 0)
	{
		printf("[exec_redirect] - Great\n");
		open_file(cmds, cmds->current->type);
	}
	if (ft_strcmp(cmds->current->type, "DGREAT") == 0)
	{
		printf("[exec_redirect] - D Great\n");
		open_file(cmds, cmds->current->type);
	}
	if (ft_strcmp(cmds->current->type, "DLESS") == 0)
	{
		printf("[exec_redirect] - DLESS\n");
		open_file(cmds, cmds->current->type);
	}
	if (ft_strcmp(cmds->current->type, "LESS") == 0)
	{
		printf("[exec_redirect] - LESS\n");
		open_file(cmds, cmds->current->type);
	}
}

void	run_node(t_cmds *cmds)
{
	int	type_command;

	type_command = -1;
	if (cmds->current->disabled == 0)
	{
		if (ft_strcmp(cmds->current->type, "WORD") == 0)
		{
			printf("[run_node] - Sou um WORD agora!----!\n");
			printf("position: %d\n", cmds->current->position);
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
		else
		{
			printf("[run_node] - Sou um REDIRECT agora!----!\n");
			exec_redirect(cmds);
		}
	}
	else
		return ;
}
