/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antthoma <antthoma@student.42sp.org.br>    +#+  +:+       +#+        */
/*       calbert  <calbert@student.42sp.org.br>   +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 02:55:02 by antthoma          #+#    #+#             */
/*   Updated: 2023/04/26 00:17:13 by antthoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* Example of a command list
Command local_commands[] = {
	{"echo", echo_adapter},
	{"pwd", pwd_adapter}
};
*/

void	execute_cmd(t_cmds *cmds)
{
	if (cmds->cmd_finded->name) {
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
}
