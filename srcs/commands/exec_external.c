/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_external_cmd.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caalbert <caalbert@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 02:55:02 by antthoma          #+#    #+#             */
/*   Updated: 2023/06/06 10:21:31 by caalbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	exec_external(t_cmds *cmds)
{
	pid_t	pid;
	char	*path;
	int		child_return_status;

	cmds->exit_code.code = 0;
	if (ft_strcmp(cmds->current->type, "WORD") == 0)
	{
		path = get_fullpath(cmds);
		cmds->current->split_args = ft_split(cmds->current->phrase, ' ');
		pid = fork();
		if (pid == -1) {
			perror("fork");
		}
		if (pid == 0)
		{
			run_strategy(cmds);
			execve(path, cmds->current->phrase_parsed, cmds->envs);
			perror("execve");
		}
		if (pid > 0)
			waitpid(pid, &child_return_status, 0);
		free(path);
	}
	free_split(cmds->current->split_args);
	cmds->exit_code.code = WEXITSTATUS(child_return_status);
}
