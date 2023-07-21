/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin_cmd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caalbert <caalbert@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 02:55:02 by antthoma          #+#    #+#             */
/*   Updated: 2023/06/06 10:21:31 by caalbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	exec_builtin(t_cmds *cmds)
{
	size_t	i;
	pid_t	pid;
	int		child_return_status;

	i = 0;
	while (i < cmds->num_cmds)
	{
		if (ft_strcmp(cmds->current->cmd_name, cmds->arr_cmds[i].name) == 0)
		{
			cmds->current->cmd_builtin = &cmds->arr_cmds[i];
			break ;
		}
		i++;
	}
	if (ft_strcmp(cmds->current->cmd_name, "exit") == 0)
		current->cmd_builtin->execute(cmds);
	else
	{
		pid = fork();
		if (pid == -1)
		{
			perror("fork");
			exit(EXIT_FAILURE);
		}
		else if (pid == 0)
		{
			cmds->current->cmd_builtin->execute(cmds);
			exit(EXIT_SUCCESS);
		}
		else
			waitpid(pid, &child_return_status, 0);
	}
}
