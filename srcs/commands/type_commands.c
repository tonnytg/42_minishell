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

	if (ft_strcmp(current->type, "WORD") == 0)
	{
		path = get_fullpath(current);
		current->split_args = ft_split(current->phrase, ' ');
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
		free(path);
	}
	free_split(current->split_args);
}

int	check_type_command(t_cmds *cmds, t_cmd_node *current)
{
	size_t	i;
	char	*path;

	i = 0;
	load_commands(current);
	while (i < cmds->num_cmds)
	{
		if (ft_strcmp(current->cmd_name, cmds->arr_cmds[i].name) == 0)
			return (0);
		i++;
	}
	path = get_fullpath(current);
	if (path != NULL)
	{
		free(path);
		return (1);
	}
	return (-1);
}
