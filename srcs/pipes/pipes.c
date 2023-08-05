/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caalbert <caalbert@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 02:55:02 by antthoma          #+#    #+#             */
/*   Updated: 2023/06/06 10:21:31 by caalbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	count_pipes(t_cmds *cmds, char *str)
{
	int	i;
	int	count_pipe;

	i = 0;
	count_pipe = 0;
	while (str[i] != '\0')
	{
		if ((str[i] == '\'' || str[i] == '\"')
			&& cmds->is_quote_opened == 0)
			cmds->is_quote_opened = 1;
		if ((str[i] == '\'' || str[i] == '\"')
			&& cmds->is_quote_opened == 1)
			cmds->is_quote_opened = 0;
		if (str[i] == '|' && cmds->is_quote_opened == 0)
			count_pipe++;
		i++;
	}
	return (count_pipe);
}

void	open_pipe(t_cmds *cmds)
{
	t_cmd_node	*current;

	current = cmds->cmd_list;
	while (current != NULL)
	{
		if (ft_strcmp(current->type, "WORD") != 0)
		{
			if (pipe(current->fd) < 0)
				exit (write (1, "[open_pipe] - Pipe error\n", 12));
			current->fd_is_active = 1;
		}
		current = current->next;
	}
}

void	connect_nodes_with_pipes(t_cmds *cmds)
{
	int			count;

	open_pipe(cmds);
	count = 0;
	cmds->current = cmds->cmd_list;
	while (cmds->current != NULL)
	{
		if (cmds->current->prev == NULL
			&& cmds->current->next != NULL
			&& ft_strcmp(cmds->current->next->type, "WORD") != 0)
		{
			cmds->current->position = HEAD;
			cmds->current->fd_ptr_input = NULL;
			cmds->current->fd_ptr_output = cmds->current->next->fd;
		}
		if (cmds->current->prev != NULL
			&& cmds->current->next != NULL
			&& ft_strcmp(cmds->current->type, "WORD") != 0)
		{
			cmds->current->position = MID;
			cmds->current->fd_ptr_input = NULL;
			cmds->current->fd_ptr_output = NULL;
			if (cmds->current->next->fd_is_active == 0
				&& ft_strcmp(cmds->current->next->type, "WORD") == 0)
			{
				cmds->current->next->fd_ptr_input = cmds->current->fd;
				cmds->current->next->fd_ptr_output = NULL;
			}
		}
		if (cmds->current->prev != NULL
			&& ft_strcmp(cmds->current->prev->type, "WORD") == 0
			&& cmds->current->next != NULL
			&& ft_strcmp(cmds->current->type, "WORD") == 0)
		{
			cmds->current->position = MID;
			if (cmds->current->fd_ptr_output == NULL)
			{
				if (cmds->current->next != NULL
					&& ft_strcmp(cmds->current->next->type, "WORD") != 0)
				{
					cmds->current->fd_ptr_output = cmds->current->next->fd;
				}
			}
		}
		if (cmds->current->next == NULL
			&& cmds->current->prev != NULL
			&& ft_strcmp(cmds->current->type, "WORD") == 0)
		{
			cmds->current->position = TAIL;
			cmds->current->fd_ptr_output = NULL;
		}
		count++;
		cmds->current = cmds->current->next;
	}
}
