/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caalbert <caalbert@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 21:16:46 by caalbert          #+#    #+#             */
/*   Updated: 2023/07/01 20:59:06 by caalbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// int	export_adapter(t_cmds *cmds)
// {
// 	char	*var_name;
// 	char	*var_value;

// 	var_name = NULL;
// 	var_value = NULL;
// 	if (cmds->input->cmd_args[1] != '\0')
// 	{
// 		var_name = &cmds->input->cmd_args[1];
// 		var_value = &cmds->input->cmd_args[2];
// 		if (setenv(var_name, var_value, 1) != 0)
// 		{
// 			perror("Error to export var");
// 			return (1);
// 		}
// 	}
// 	else
// 		return (1);
// 	return (0);
// }

static void	free_args(char **args)
{
	int	i;

	i = 0;
	while (args[i] != NULL)
	{
		free(args[i]);
		i++;
	}
	free(args);
}

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
	free_args(args);
	return (result);
}
