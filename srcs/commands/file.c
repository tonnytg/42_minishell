/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caalbert <caalbert@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 02:55:02 by antthoma          #+#    #+#             */
/*   Updated: 2023/06/06 10:21:31 by caalbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	open_file(t_cmds *cmds, char *type)
{
	printf("open file fd in node %p\n", cmds);

	if (ft_strcmp(type, "DGREAT") == 0)
	{
		printf("[open_file] - File type is DGREAT\n");
	}

	if (ft_strcmp(type, "GREAT") == 0)
	{
		printf("[open_file] - File type is GREAT\n");
	}

	if (ft_strcmp(type, "LESS") == 0)
	{
		printf("[open_file] - File type is LESS\n");
	}

	if (ft_strcmp(type, "DLESS") == 0)
	{
		printf("[open_file] - File type is DLESS\n");
	}
}