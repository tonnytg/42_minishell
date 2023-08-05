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

void	set_head_word_fd(t_cmds *cmds)
{
	if (cmds->current->prev == NULL
		&& cmds->current->next != NULL
		&& ft_strcmp(cmds->current->next->type, "WORD") != 0)
	{
		cmds->current->position = HEAD;
		cmds->current->fd_ptr_input = NULL;
		cmds->current->fd_ptr_output = cmds->current->next->fd;
	}
}

void	set_mid_word_fd(t_cmds *cmds)
{
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
}

/* TODO: We need review this because type equal WORD */
void	set_mid_redirect_fd(t_cmds *cmds)
{
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
}

void	set_tail_word_fd(t_cmds *cmds)
{
	if (cmds->current->next == NULL
		&& cmds->current->prev != NULL
		&& ft_strcmp(cmds->current->type, "WORD") == 0)
	{
		cmds->current->position = TAIL;
		cmds->current->fd_ptr_output = NULL;
	}
}
