/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caalbert <caalbert@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 02:55:02 by antthoma          #+#    #+#             */
/*   Updated: 2023/06/03 22:47:52 by caalbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	execute_cmd(t_cmds *cmds)
{
	if (cmds->cmd_finded->name)
	{
		cmds->exit_code.last_cmd = cmds->input->cmd_name;
		cmds->exit_code.code = cmds->cmd_finded->execute(cmds->input->cmd_args);
	}
}

void	set_commands(t_cmds *cmds)
{
	cmds->num_cmds = 3;
	cmds->arr_cmds = malloc(sizeof(t_command) * cmds->num_cmds);
	cmds->arr_cmds[0].name = malloc(sizeof(char) * (strlen("echo") + 1));
	ft_strlcpy(cmds->arr_cmds[0].name, "echo", 5);
	cmds->arr_cmds[0].execute = echo_adapter;
	cmds->arr_cmds[1].name = malloc(sizeof(char) * (strlen("pwd") + 1));
	ft_strlcpy(cmds->arr_cmds[1].name, "pwd", 4);
	cmds->arr_cmds[1].execute = pwd_adapter;
	cmds->arr_cmds[2].name = malloc(sizeof(char) * (strlen("exit") + 1));
	ft_strlcpy(cmds->arr_cmds[2].name, "exit", 5);
	cmds->arr_cmds[2].execute = exit_adapter;
		cmds->arr_cmds[3].name = malloc(sizeof(char) * (strlen("export") + 1));
	strcpy(cmds->arr_cmds[3].name, "export");
	cmds->arr_cmds[3].execute = export_adapter;
}
