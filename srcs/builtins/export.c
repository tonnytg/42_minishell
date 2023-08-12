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
	if (cmds->envs != NULL)
	{
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
	}
	if (trigger == 0)
	{
		envs[i] = ft_strdup(key_and_value);
		i++;
	}
	envs[i] = NULL;
}

char	*convert_values(t_cmds *cmds, const char *value)
{
	t_env_convert	*env_c;
	char			*result;

	env_c = ft_calloc(1, sizeof(t_env_convert));
	env_c->arr = ft_calloc(256, sizeof(char *) + 5);
	while (value[env_c->i] != '\0')
	{
		search_for_word(cmds, env_c, value);
		search_for_rest(env_c, value);
		env_c->i++;
	}
	if (env_c->rest_active == 1)
		save_rest(env_c);
	if (env_c->trigger == 1)
		save_converted_word(cmds, env_c);
	env_c->arr[env_c->a] = NULL;
	env_c->converted_arr = concatenate_strings(env_c->arr, ':');
	free_arr(env_c->arr);
	result = ft_strdup(env_c->converted_arr);
	free(env_c->converted_arr);
	free(env_c);
	return (result);
}

int	set_env_var(t_cmds *cmds, char *key, char *value)
{
	char	**envs;
	char	*new_key;
	char	*key_and_value;
	char	*new_value;

	new_value = convert_values(cmds, value);
	if (cmds->envs == NULL && cmds->current->full_args == NULL)
		return (1);
	envs = ft_calloc(count_arr(cmds->envs) + 2, sizeof(char *));
	new_key = ft_strjoin(key, "=");
	key_and_value = ft_strjoin(new_key, new_value);
	free(new_value);
	save_envs(cmds, envs, key, key_and_value);
	free(new_key);
	free(key_and_value);
	if (cmds->envs != NULL)
		free_arr(cmds->envs);
	cmds->envs = envs;
	return (0);
}

int	export_adapter(t_cmds *cmds)
{
	char	**args;
	int		result;

	if (cmds->current->full_args == NULL
		|| (cmds->current->phrase_parsed == NULL
			&& cmds->current->phrase_parsed[1] == NULL))
		env_adapter(cmds);
	args = ft_split(cmds->current->phrase_parsed[1], '=');
	if (args != NULL && (args[0] == NULL || args[1] == NULL))
	{
		printf("minishell: export: `%s': not a valid identifier\n", args[0]);
		free_arr(args);
		return (1);
	}
	if (args == NULL)
		return (1);
	result = set_env_var(cmds, args[0], args[1]);
	free_arr(args);
	return (result);
}
