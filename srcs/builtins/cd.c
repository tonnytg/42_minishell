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
	const char	*path;

	path = cmds->input->cmd_args;
	if (chdir(path) != 0)
	{
		printf("cd: %s: No such file or directory\n", path);
		return (1);
	}
	return (0);
}
