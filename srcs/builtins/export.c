/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caalbert <caalbert@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 21:16:46 by caalbert          #+#    #+#             */
/*   Updated: 2023/07/02 11:44:14 by caalbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	set_env_var(char **args)
{
	char	*var_name;
	char	*var_value;
	int		result;

	var_name = ft_strtok(args[0], "=", 0);
	var_value = ft_strtok(NULL, "=", 0);
	if (var_name && var_value)
	{
		result = setenv(var_name, var_value, 1);
		if (result != 0)
		{
			perror("Error to export var");
			return (1);
		}
	}
	else
		return (1);
	return (0);
}

int	export_adapter(t_cmds *cmds)
{
	char	**args;
	char	**env;
	int		result;

	env = cmds->envs;
	if (cmds->input->cmd_args == NULL)
	{
		while (*env)
		{
			printf("%s\n", *env);
			env++;
		}
		return (0);
	}
	args = ft_split(cmds->input->cmd_args, ' ');
	result = set_env_var(args);
	free_arr(args);
	return (result);
}
