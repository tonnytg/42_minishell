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

// Example of a command list
// Command local_commands[] = {
// 		{"echo", echo_adapter},
// 		{"pwd", pwd_adapter}
// };
void free_commands(t_command *commands, int num_commands)
{
    int i;
    for (i = 0; i < num_commands; i++) {
        free(commands[i].name);
    }
    free(commands);
}

void	set_commands(t_cmds *cmds)
{
	cmds->num_cmds = 3;
	cmds->cmd = malloc(sizeof(t_command) * cmds->num_cmds);

	cmds->cmd[0].name = malloc(sizeof(char) * (strlen("echo") + 1));
	strcpy(cmds->cmd[0].name, "echo");
	cmds->cmd[0].execute = echo_adapter;

	cmds->cmd[1].name = malloc(sizeof(char) * (strlen("pwd") + 1));
	strcpy(cmds->cmd[1].name, "pwd");
	cmds->cmd[1].execute = pwd_adapter;

	cmds->cmd[2].name = malloc(sizeof(char) * (strlen("exit") + 1));
	strcpy(cmds->cmd[2].name, "exit");
	cmds->cmd[2].execute = exit_adapter;
}

t_command	*find_command(t_cmds *cmds, const char *name)
{
	int	i;

	i = 0;
	while (i < cmds->num_cmds)
	{
		if (strcmp(cmds->cmd[i].name, name) == 0)
		{
			return (&cmds->cmd[i]);
		}
		i++;
	}
	return (NULL);
}

int	main(void)
{
	char		input[256];
	char		*command_name;
	char		*command_arg;
	t_command	*command;
	t_cmds		*cmds;
	int resp;

	while (1)
	{
		// msg in prompt
		ft_printf("> ");
		fgets(input, sizeof(input), stdin);
		input[strcspn(input, "\n")] = 0;

		// parse input
		command_name = strtok(input, " ");
		command_arg = strtok(NULL, "");

		// set commands
		cmds = ft_calloc(1, sizeof(t_cmds));
		set_commands(cmds);

		// find command
		command = find_command(cmds, command_name);
		if (command == NULL)
		{
			// print error msg and skip loop
			ft_printf("minishell: %s: command not found\n", command_name);
			continue ;
		}
		// execute command
		resp = command->execute(command_arg);
		if (resp == 1)
		{
			free_commands(cmds->cmd, cmds->num_cmds);
			free(cmds);
			break ;
		}
	}
	return (0);
}
