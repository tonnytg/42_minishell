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

void	save_envs(t_cmds *cmds, char **envs, char *key, char *key_and_value)
{
	int	trigger;
	int	i;

	i = 0;
	trigger = 0;
	while (cmds->envs[i] != NULL)
	{
		if (ft_strncmp(cmds->envs[i], key, ft_strlen(key)) == 0)
		{
			envs[i] = ft_strdup(key_and_value);
			trigger = 1;
		}
		else
			envs[i] = ft_strdup(cmds->envs[i]);
		i++;
	}
	if (trigger == 0)
	{
		envs[i] = ft_strdup(key_and_value);
		i++;
	}
	envs[i] = NULL;
}

int	set_env_var(t_cmds *cmds, char *key, char *value)
{
	char	**envs;
	char	*new_key;
	char 	*key_and_value;

	if (cmds->envs == NULL)
		return (1);
	envs = ft_calloc(count_arr(cmds->envs) + 2, sizeof(char *));
	new_key = ft_strjoin(key, "=");
	key_and_value = ft_strjoin(new_key, value);
	save_envs(cmds, envs, key, key_and_value);
	free(new_key);
	free(key_and_value);
	free_arr(cmds->envs);
	cmds->envs = envs;
	return (0);
}

int	export_adapter(t_cmds *cmds)
{
	char	**args;
	char	**env;
	int		result;

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
	args = ft_split(cmds->current->phrase_parsed[1], '=');
	result = set_env_var(cmds, args[0], args[1]);
	free_arr(args);
	return (result);
}
