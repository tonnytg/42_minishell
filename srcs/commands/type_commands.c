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

int	check_type_command(t_cmds *cmds)
{
	size_t	i;
	char	*path;

	i = 0;
	load_commands(cmds);
	while (i < cmds->num_cmds)
	{
		if (ft_strcmp(cmds->current->cmd_name, cmds->arr_cmds[i].name) == 0)
			return (0);
		i++;
	}
	path = get_fullpath(cmds);
	if (path != NULL)
	{
		free(path);
		return (1);
	}
	return (-1);
}
