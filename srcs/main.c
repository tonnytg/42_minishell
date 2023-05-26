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

void	free_commands(t_cmds *cmds)
{
	int	i;

	i = 0;
	while (i < cmds->num_cmds)
	{
		free(cmds->arr_cmds[i].name);
		i++;
	}
	free(cmds->arr_cmds);
	free(cmds->cmd_finded);
	free(cmds->input);
	free(cmds);
}

void	execute_cmd(t_cmds *cmds)
{
	cmds->exit_code.last_cmd = cmds->input->cmd_name;
	cmds->exit_code.code = cmds->cmd_finded->execute(cmds->input->cmd_args);
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
	int		exit_code;

	cmds = malloc(sizeof(t_cmds) * 1);
	cmds->input = malloc(sizeof(t_input) * 1);
	cmds->cmd_finded = malloc(sizeof(t_command));
	cmds->exit_code.code = 0;
	set_commands(cmds);
	while (1)
	{
		read_keyboard(cmds);
		if (cmds->input->cmd_name == NULL)
			continue ;
		find_command(cmds);
		execute_cmd(cmds);
		exit_code = cmds->exit_code.code;
		if (is_exit(cmds))
			break ;
	}
	free_commands(cmds);
	return (exit_code);
}
