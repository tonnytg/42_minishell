/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caalbert <caalbert@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 02:55:02 by antthoma          #+#    #+#             */
/*   Updated: 2023/08/10 22:58:29 by caalbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	find_command(t_cmds *cmds)
{
	size_t	i;

	i = 0;
	while (i < cmds->num_cmds && cmds->input->cmd_name != NULL)
	{
		if (ft_strcmp(cmds->arr_cmds[i].name, cmds->input->cmd_name) == 0)
		{
			ft_memcpy(cmds->cmd_finded, &cmds->arr_cmds[i], sizeof(t_command));
			return ;
		}
		i++;
	}
	ft_printf("minishell: %s: command not found\n", cmds->current->cmd_name);
	cmds->exit_code.code = 127;
	cmds->cmd_finded->name = NULL;
}

void	set_commands(t_cmds *cmds)
{
	size_t		i;
	t_command	command_mapping[8];

	command_mapping[0] = (t_command){ECHO_BUILTIN, echo_adapter};
	command_mapping[1] = (t_command){CD_BUILTIN, cd_adapter};
	command_mapping[2] = (t_command){PWD_BUILTIN, pwd_adapter};
	command_mapping[3] = (t_command){EXPORT_BUILTIN, export_adapter};
	command_mapping[4] = (t_command){UNSET_BUILTIN, unset_adapter};
	command_mapping[5] = (t_command){ENV_BUILTIN, env_adapter};
	command_mapping[6] = (t_command){EXIT_BUILTIN, exit_adapter};
	command_mapping[7] = (t_command){TEST_FD, test_fd_adapter};
	cmds->num_cmds = sizeof(command_mapping) / sizeof(t_command);
	cmds->arr_cmds = ft_calloc(cmds->num_cmds, sizeof(t_command));
	cmds->previous_dir = NULL;
	i = 0;
	while (i < cmds->num_cmds)
	{
		cmds->arr_cmds[i].name = command_mapping[i].name;
		cmds->arr_cmds[i].execute = command_mapping[i].execute;
		i++;
	}
}

void	load_commands(t_cmds *cmds)
{
	if (cmds->current->phrase_parsed != NULL)
	{
		if (cmds->current->phrase_parsed[0] != NULL)
			cmds->current->cmd_name = ft_strdup(
					cmds->current->phrase_parsed[0]);
		if (cmds->current->phrase_parsed[1] != NULL)
			cmds->current->full_args = concatenate_strings(
					cmds->current->phrase_parsed + 1, 0);
	}
}

void	close_pipes(t_cmds *cmds)
{
	if (cmds->current->prev != NULL
		&& cmds->current->next != NULL)
	{
		if (ft_strcmp(cmds->current->type, "WORD") != 0)
		{
			close(cmds->current->fd[1]);
		}
	}
}

void	execute_cmd(t_cmds *cmds)
{
	cmds->current = cmds->cmd_list;
	while (cmds->current != NULL)
	{
		close_pipes(cmds);
		run_node(cmds);
		cmds->current = cmds->current->next;
	}
}
