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

void	open_pipe(t_cmd_node *current)
{
	printf("open pipe fd in node %p\n", current);
	if (pipe(current->fd) < 0)
		exit (write (1, "Pipe error\n", 12));
}
