/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caalbert <caalbert@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 10:14:31 by caalbert          #+#    #+#             */
/*   Updated: 2023/06/13 13:36:19 by caalbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	unset_adapter(t_cmds *cmds)
{
	if (getenv(cmds->input->cmd_args) != NULL)
	{
		unsetenv(cmds->input->cmd_args);
		if (getenv(cmds->input->cmd_args) == NULL)
			return (0);
		else
			return (1);
	}
	else
		return (1);
}

	/*
	(void) cmds;
	printf("⚠️ Need to create!!! ⚠️\n");
	return (0);
	*/