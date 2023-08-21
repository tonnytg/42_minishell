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
	free_arr(cmds->current->phrase_parsed);
	free(cmds->current->cmd_name);
	free(cmds->current->full_args);
	free_arr(cmds->envs);
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

int	skip_commands_child(t_cmds *cmds)
{
	if (ft_strcmp(cmds->current->cmd_name, "exit") == 0)
		return (1);
	else if (ft_strcmp(cmds->current->cmd_name, "cd") == 0)
		return (1);
	else if (ft_strcmp(cmds->current->cmd_name, "env") == 0)
		return (1);
	else if (ft_strcmp(cmds->current->cmd_name, "export") == 0)
		return (1);
	else if (ft_strcmp(cmds->current->cmd_name, "unset") == 0)
		return (1);
	return (0);
}

void	exec_local_builtin(t_cmds *cmds)
{
	set_piped_stdout(cmds);
	cmds->current->cmd_builtin->execute(cmds);
	set_restore_stdout(cmds);
}

void	exec_builtin(t_cmds *cmds)
{
	pid_t	pid;
	int		child_return_status;

	define_cmd_to_exec(cmds);
	if (skip_commands_child(cmds) == 1)
		exec_local_builtin(cmds);
	else
	{
		pid = fork();
		cmds->current->c_pid = pid;
		if (pid == -1)
			exit(EXIT_FAILURE);
		else if (pid == 0)
		{
			run_strategy(cmds);
			cmds->current->cmd_builtin->execute(cmds);
			child_return_status = cmds->exit_code.code;
			free_builtin_cmd(cmds);
			exit(child_return_status);
		}
		else
			waitpid(pid, &child_return_status, 0);
		cmds->exit_code.code = WEXITSTATUS(child_return_status);
	}
}
