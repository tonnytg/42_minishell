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

t_command	*find_command(const char *name)
{
	int			i;
	int			num_commands;
	t_command	*g_commands;

	num_commands = 0;
	g_commands = malloc(sizeof(t_command) * 2);
	g_commands[num_commands].name = malloc(sizeof(char) * (strlen("echo") + 1));
	strcpy(g_commands[num_commands].name, "echo");
	g_commands[num_commands].execute = echo_adapter;
	num_commands++;
	i = 0;
	while (i < num_commands)
	{
		if (strcmp(g_commands[i].name, name) == 0)
		{
			return (&g_commands[i]);
		}
		i++;
	}
	return (NULL);
}

int	main(void)
{
	char	input[256];
	char	*command_name;
	char	*command_arg;
	Command	*command;

	while (1)
	{
		ft_printf("> ");
		fgets(input, sizeof(input), stdin);
		input[strcspn(input, "\n")] = 0;
		command_name = strtok(input, " ");
		command_arg = strtok(NULL, "");
		command = find_command(command_name);
		if (command == NULL)
		{
			ft_printf("Comando não encontrado\n");
			continue ;
		}
		command->execute(command_arg);
	}
	return (0);
}
