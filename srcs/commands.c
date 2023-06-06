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

#include "../includes/minishell.h"

void	execute_cmd(t_cmds *cmds)
{
	if (cmds->cmd_finded->name)
	{
		cmds->exit_code.last_cmd = cmds->input->cmd_name;
		cmds->exit_code.code = cmds->cmd_finded->execute(cmds);
	}
}

void	set_commands(t_cmds *cmds)
{
	size_t		i;
	t_command	command_mapping[7];

	command_mapping[0] = (t_command){ECHO_BUILTIN, echo_adapter};
	command_mapping[1] = (t_command){CD_BUILTIN, cd_adapter};
	command_mapping[2] = (t_command){PWD_BUILTIN, pwd_adapter};
	command_mapping[3] = (t_command){EXPORT_BUILTIN, export_adapter};
	command_mapping[4] = (t_command){UNSET_BUILTIN, unset_adapter};
	command_mapping[5] = (t_command){ENV_BUILTIN, env_adapter};
	command_mapping[6] = (t_command){EXIT_BUILTIN, exit_adapter};
	cmds->num_cmds = sizeof(command_mapping) / sizeof(t_command);
	cmds->arr_cmds = malloc(sizeof(t_command) * cmds->num_cmds);
	i = 0;
	while (i < cmds->num_cmds)
	{
		cmds->arr_cmds[i].name = command_mapping[i].name;
		cmds->arr_cmds[i].execute = command_mapping[i].execute;
		i++;
	}
}
