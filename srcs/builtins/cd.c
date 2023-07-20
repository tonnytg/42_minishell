/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caalbert <caalbert@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 10:13:53 by caalbert          #+#    #+#             */
/*   Updated: 2023/07/01 22:12:19 by caalbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	cd_adapter(t_cmds *cmds)
{
	const char	*dir;

	if (cmds->input->cmd_args == NULL)
	{
		dir = getenv("HOME");
		if (dir == NULL)
		{
			fprintf(stderr, "cd: HOME not set\n");
			return (1);
		}
	}
	else
		dir = cmds->input->cmd_args;
	if (chdir(cmds->input->cmd_args) != 0)
	{
		perror("cd");
		return (1);
	}
	return (0);
}
