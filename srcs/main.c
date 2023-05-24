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
		if (command == NULL && data.cmd_name != NULL)
		{
			ft_printf("minishell: %s: command not found\n", data.cmd_name);
			continue ;
		}
		if (data.cmd_name != NULL)
			resp = command->execute(data.cmd_arg);
		if (resp == 1)
			break ;
	}
	free_commands(cmds);
	return (0);
}
