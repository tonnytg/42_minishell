/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_commands.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caalbert <caalbert@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 02:55:02 by antthoma          #+#    #+#             */
/*   Updated: 2023/06/06 10:21:31 by caalbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	exec_builtin(t_cmds *cmds, t_cmd_node *current)
{
	size_t	i;

	i = 0;
	while (i < cmds->num_cmds)
	{
		if (ft_strcmp(current->cmd_name, cmds->arr_cmds[i].name) == 0)
		{
			current->cmd_builtin = &cmds->arr_cmds[i];
			break ;
		}
		i++;
	}
	current->cmd_builtin->execute(cmds);
}

void	exec_external(t_cmds *cmds, t_cmd_node *current)
{
	pid_t	pid;
	char	*path;

	path = get_fullpath(current);
	current->split_args = ft_split(current->phrase, ' ');
	if (ft_strcmp(current->type, "WORD") == 0)
	{
		pid = fork();
		if (pid == -1)
			perror("fork");
		if (pid == 0)
		{
			execve(path, current->split_args, cmds->envs);
			perror("execve");
		}
		if (pid > 0)
			waitpid(pid, NULL, 0);
	}
}

int	check_type_command(t_cmds *cmds, t_cmd_node *current)
{
	int	i;

	i = 0;
	load_commands(current);
	while (cmds->arr_cmds[i].name != NULL)
	{
		if (ft_strcmp(current->cmd_name, cmds->arr_cmds[i].name) == 0)
		{
			return (0);
		}
		i++;
	}
	if (get_fullpath(current) != NULL)
		return (1);
	return (-1);
}
