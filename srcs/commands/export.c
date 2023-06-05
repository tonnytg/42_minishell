/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caalbert <caalbert@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 21:55:19 by caalbert          #+#    #+#             */
/*   Updated: 2023/06/04 21:12:47 by caalbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	export_adapter(t_cmds *cmds)
{
	char	*var_name;
	char	*var_value;

	var_name = NULL;
	var_value = NULL;
	if (cmds->input->cmd_args[1] != NULL)
	{
		var_name = cmds->input->cmd_args[1];
		var_value = cmds->input->cmd_args[2];
		if (setenv(var_name, var_value, 1) != 0)
		{
			perror("Error to export var");
			return (1);
		}
	}
	else
		return (1);
	return (0);
}
