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

/* Redirect output to file */
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
			if (ft_strcmp(cmds->current->next->next->type, "WORD") == 0)
			{
				dup2(cmds->current->next->fd[0], STDIN_FILENO);
				dup2(cmds->current->next->next->next->fd[1], STDOUT_FILENO);
			}
		}
	}
	else
		cmds->current->next->disabled = 1;
}

void	set_strategy(t_cmds *cmds)
{
	t_strategy	*s;
	char		*msg;
	char		buffer[1024];
	int			file;
	ssize_t		bytes_read;

	s = ft_calloc(1, sizeof(t_strategy));
	cmds->current = cmds->cmd_list;
	while (cmds->current != NULL)
	{
		if (ft_strcmp(cmds->current->type, "LESS") == 0)
		{
			file = open("file.txt", O_RDONLY);
			if (file < 1)
			{
				perror("error: file descriptor not opened!\n");
			}
			bytes_read = read(file, buffer, sizeof(buffer) - 1);
			if (bytes_read < 0)
			{
				perror("read");
				exit(EXIT_FAILURE);
			}
			buffer[bytes_read] = '\0';
			msg = ft_strdup(buffer);
			if (!msg)
				return ;
			write(cmds->current->fd[1], msg, ft_strlen(msg));
			close(cmds->current->fd[1]);
			free(msg);
			if (ft_strcmp(cmds->current->type, "WORD") != 0)
			{
				cmds->current->disabled = 1;
				cmds->current->next->disabled = 1;
			}
			cmds->current->prev->strategy = S_RECEIVER;
		}
		if (ft_strcmp(cmds->current->type, "DLESS") == 0)
		{
			here_doc(cmds);
			cmds->current->prev->strategy = S_SKIP_NEXT_FD;
			cmds->current->disabled = 1;
			cmds->current->next->disabled = 1;
			close(cmds->current->fd[1]);
		}
		cmds->current = cmds->current->next;
	}
	cmds->strategy = 0;
	free(s);
}
