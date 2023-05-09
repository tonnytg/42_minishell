/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c.                                            :+:      :+:    :+:   */
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

void	set_commands(t_cmds *cmds)
{
	cmds->num_cmds = 3;
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
}

t_command	*find_command(t_cmds *cmds, const char *name)
{
	int	i;

	i = 0;
	while (i < cmds->num_cmds)
	{
		if (ft_strcmp(cmds->cmd[i].name, name) == 0)
		{
			return (&cmds->cmd[i]);
		}
		i++;
	}
	return (NULL);
}

void	read_keyboard(t_input *data)
{
	ft_printf("> ");
	fgets(data->input, sizeof(data->input), stdin);
	data->input[strcspn(data->input, "\n")] = 0;
	data->cmd_name = strtok(data->input, " ");
	data->cmd_arg = strtok(NULL, "");
}

int	main(void)
{
	t_input		data;
	t_command	*command;
	t_cmds		*cmds;
	int			resp;

	ft_bzero(&data, sizeof(t_input));
	cmds = ft_calloc(1, sizeof(t_cmds));
	set_commands(cmds);
	while (1)
	{
		read_keyboard(&data);
		command = find_command(cmds, data.cmd_name);
		if (command == NULL)
		{
			ft_printf("minishell: %s: command not found\n", data.cmd_name);
			continue ;
		}
		resp = command->execute(data.cmd_arg);
		if (resp == 1)
		{
			break ;
		}
	}
	free_commands(cmds);
	return (0);
}
