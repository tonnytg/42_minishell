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

int	set_env_var(t_cmds *cmds, char *key, char *value)
{
	char	**envs;
	char	*new_key_value;
	int		envs_len;
	int		i;

	if (cmds->envs == NULL)
		return (1);
	envs_len = count_arr(cmds->envs);
	envs = ft_calloc(envs_len + 2, sizeof(char *));
	new_key_value = ft_strjoin(key, "=");
	new_key_value = ft_strjoin(new_key_value, value);
	i = 0;
	while (cmds->envs[i] != NULL)
	{
		envs[i] = ft_strdup(cmds->envs[i]);
		i++;
	}
	envs[i] = ft_strdup(new_key_value);
	envs[i + 1] = NULL;
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
	args = ft_split(cmds->current->full_args, ' ');
	char *key = args[0];
	char *value = args[1];
	result = set_env_var(cmds, key, value);
	free_arr(args);
	return (result);
}
