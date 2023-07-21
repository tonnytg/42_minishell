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

void	free_builtin_cmd(t_cmds *cmds)
{
	int	i;

	i = 0;
	while (cmds->envs[i])
	{
		free(cmds->envs[i]);
		i++;
	}
	free(cmds->envs);
	free_cmd_nodes(cmds->cmd_list);
	free_commands(cmds);
}

void	define_cmd_to_exec(t_cmds *cmds)
{
	size_t	i;

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
}

void	exec_builtin(t_cmds *cmds)
{
	pid_t	pid;
	int		child_return_status;

	define_cmd_to_exec(cmds);
	if (ft_strcmp(cmds->current->cmd_name, "exit") == 0)
		cmds->current->cmd_builtin->execute(cmds);
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
			free_builtin_cmd(cmds);
			exit(EXIT_SUCCESS);
		}
		else
			waitpid(pid, &child_return_status, 0);
	}
}
