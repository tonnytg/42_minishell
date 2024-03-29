/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caalbert <caalbert@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 02:55:02 by antthoma          #+#    #+#             */
/*   Updated: 2023/08/09 00:18:58 by caalbert         ###   ########.fr       */
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
	cmds->current = cmds->cmd_list;
	while (cmds->current != NULL)
	{
		if (ft_strcmp(cmds->current->type, "WORD") != 0)
		{
			if (pipe(cmds->current->fd) < 0)
				printf("pipe has error\n");
			cmds->current->fd_is_active = 1;
		}
		cmds->current = cmds->current->next;
	}
}

void	connect_nodes_with_pipes(t_cmds *cmds)
{
	if (cmds->strategy_error.code == -1)
		return ;
	open_pipe(cmds);
	cmds->current = cmds->cmd_list;
	while (cmds->current != NULL)
	{
		set_head_word_fd(cmds);
		set_mid_word_fd(cmds);
		set_mid_redirect_fd(cmds);
		set_tail_word_fd(cmds);
		cmds->current = cmds->current->next;
	}
}
