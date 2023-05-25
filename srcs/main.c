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

void	execute_cmd(t_cmds *cmds)
{
//	resp = command->execute(data.cmd_arg);
	cmds->exit_code.last_cmd = cmds->input->cmd_name;
	cmds->exit_code.code = cmds->cmd_finded.execute(cmds->input->cmd_args);
}

int	is_exit(t_cmds *cmds)
{
	if (ft_strcmp(cmds->exit_code.last_cmd, "exit") == 0)
		return (1);
	return (0);
}

int	main(void)
{
	t_cmds	*cmds;

	ft_bzero(&cmds, sizeof(t_cmds) * 1);
//	ft_printf("set commands\n");
//	set_commands(cmds);
//	while (1)
//	{
//		ft_printf("read commands\n");
//		read_keyboard(cmds);
//		ft_printf("find commands\n");
//		find_command(cmds);
//		ft_printf("exec commands\n");
//		execute_cmd(cmds);
//		if (is_exit(cmds))
//			break ;
//	}
	free_commands(cmds);
	return (0);
}
