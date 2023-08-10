/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strategy.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caalbert <caalbert@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 02:55:02 by antthoma          #+#    #+#             */
/*   Updated: 2023/06/06 10:21:31 by caalbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* Redirect output to file TODO: Diferente pode causar um problma */
void	run_strategy(t_cmds *cmds)
{
	if (ft_strcmp(cmds->current->type, "WORD") == 0)
	{
		if (cmds->current->next && cmds->current->strategy != S_RECEIVER)
		{
			dup2(cmds->current->fd_ptr_output[1], STDOUT_FILENO);
		}
		if (cmds->current->strategy == S_RECEIVER)
		{
			dup2(cmds->current->next->fd[0], STDIN_FILENO);
		}
		if (cmds->current->strategy == S_SKIP_NEXT_FD)
		{
			dup2(cmds->current->next->fd[0], STDIN_FILENO);
			dup2(cmds->current->next->next->next->fd[1], STDOUT_FILENO);
		}
		if (cmds->current->strategy == S_DLESS_CURRENT)
		{
			dup2(cmds->current->next->fd[0], STDIN_FILENO);
		}
		run_strategy_piped(cmds);
	}
}

char	*read_from_file(void)
{
	char	*msg;
	char	buffer[1024];
	int		bytes_read;
	int		file;
	int		result;

	result = access("file.txt", F_OK);
	if (result != 0)
		return (NULL);
	file = open("file.txt", O_RDONLY);
	if (file < 1)
		perror("error: file descriptor not opened!\n");
	bytes_read = read(file, buffer, sizeof(buffer) - 1);
	if (bytes_read < 0)
		exit(EXIT_FAILURE);
	buffer[bytes_read] = '\0';
	msg = ft_strdup(buffer);
	if (!msg)
		return (NULL);
	return (msg);
}

void	write_in_fd(t_cmds *cmds, char *msg)
{
	if (msg == NULL)
		return ;
	write(cmds->current->fd[1], msg, ft_strlen(msg));
	close(cmds->current->fd[1]);
	free(msg);
}

void	set_strategy(t_cmds *cmds)
{
	cmds->current = cmds->cmd_list;
	while (cmds->current != NULL)
	{
		check_less(cmds);
		check_dless(cmds);
		check_pipe(cmds);
		if (cmds->exit_code.code != 0)
			return ;
		cmds->current = cmds->current->next;
	}
	cmds->strategy = 0;
}
