/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caalbert <caalbert@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 21:55:19 by caalbert          #+#    #+#             */
/*   Updated: 2023/06/03 23:40:29 by caalbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	export_adapter(const char *arg)
{
	const char	**args;
	char		*var_name;
	char		*var_value;

	var_name = NULL;
	var_value = NULL;
	args = (const char **)arg;
	if (args[1] != NULL)
	{
		var_name = args[1];
		var_value = args[2];
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
