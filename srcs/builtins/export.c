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

void	save_envs(t_cmds *cmds, char **envs, char *key, char *new_key_value)
{
	int	trigger;
	int	i;

	i = 0;
	trigger = 0;
	while (cmds->envs[i] != NULL)
	{
		if (ft_strncmp(cmds->envs[i], key, ft_strlen(key)) == 0)
		{
			envs[i] = ft_strdup(new_key_value);
			trigger = 1;
		}
		else
			envs[i] = ft_strdup(cmds->envs[i]);
		i++;
	}
	if (trigger == 0)
	{
		envs[i] = ft_strdup(new_key_value);
		i++;
	}
	envs[i] = NULL;
}

int	set_env_var(t_cmds *cmds, char *key, char *value)
{
	char	**envs;
	char	*new_key_value;

	if (cmds->envs == NULL)
		return (1);
	envs = ft_calloc(count_arr(cmds->envs) + 2, sizeof(char *));
	new_key_value = ft_strjoin(key, "=");
	new_key_value = ft_strjoin(new_key_value, value);
	save_envs(cmds, envs, key, new_key_value);
	free_arr(cmds->envs);
	cmds->envs = envs;
	return (0);
}

int	export_adapter(t_cmds *cmds)
{
	char	**args;
	char	**env;
	int		result;
	char	*value;
	char	*key;

	env = cmds->envs;
	if (cmds->current->full_args == NULL)
	{
		while (*env)
		{
			printf("%s\n", *env);
			env++;
		}
		return (0);
	}
	args = ft_split(cmds->current->full_args, '=');
	args[1] = remove_string(args[1], '"');
	key = args[0];
	value = args[1];
	result = set_env_var(cmds, key, value);
	free_arr(args);
	return (result);
}
