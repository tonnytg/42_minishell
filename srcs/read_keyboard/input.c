/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caalbert <caalbert@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 02:55:02 by antthoma          #+#    #+#             */
/*   Updated: 2023/07/02 12:43:45 by caalbert         ###   ########.fr       */
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
	ft_printf("minishell: %s: command not found\n", cmds->input->cmd_name);
	cmds->exit_code.code = 127;
	cmds->exit_code.last_cmd = cmds->input->cmd_name;
	cmds->cmd_finded->name = NULL;
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

void	read_keyboard(t_cmds *cmds)
{
	ft_printf("\033[0;32mminishell: > \033[0;0m");
	if (fgets(cmds->input->data, sizeof(cmds->input->data), stdin) == NULL)
	{
		cmds->exit = 1;
		return ;
	}
	cmds->input->data[strcspn(cmds->input->data, "\n")] = 0;
	if (cmds->input->data[0] == '\0')
	{
		cmds->input->cmd_name = NULL;
		return ;
	}
	cmds->input->datacpy = ft_strdup(cmds->input->data);
	cmds->input->cmd_name = ft_strtok(cmds->input->data, " ", 1);
	cmds->input->cmd_args = ft_strtok(NULL, "", 0);
}
