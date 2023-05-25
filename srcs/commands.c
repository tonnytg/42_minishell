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
void	free_commands(t_cmds *commands)
{
	int	i;

	i = 0;
	while (i < commands->num_cmds)
	{
		free(commands->cmd[i].name);
		i++;
	}
	free(commands->cmd);
	free(commands);
}

t_cmds	*set_commands(int num_cmds)
{
	t_cmds	*cmds;

	cmds = ft_calloc(1, sizeof(t_cmds));
	cmds->num_cmds = num_cmds;
	cmds->cmd = malloc(sizeof(t_command) * cmds->num_cmds);
	cmds->cmd[0].name = malloc(sizeof(char) * (strlen("echo") + 1));
	ft_strlcpy(cmds->cmd[0].name, "echo", 5);
	cmds->cmd[0].execute = echo_adapter;
	cmds->cmd[1].name = malloc(sizeof(char) * (strlen("pwd") + 1));
	ft_strlcpy(cmds->cmd[1].name, "pwd", 4);
	cmds->cmd[1].execute = pwd_adapter;
	cmds->cmd[2].name = malloc(sizeof(char) * (strlen("exit") + 1));
	ft_strlcpy(cmds->cmd[2].name, "exit", 5);
	cmds->cmd[2].execute = exit_adapter;
	return (cmds);
}
