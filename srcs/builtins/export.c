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

char	*convert_values(const char *value)
{
	int i;
	int	j;
	int k;
	int	trigger;
	char word[256];
	char **arr_str;
	char **arr;

	i = 0;
	j = 0;
	k = 0;
	trigger = 0;
	arr_str = ft_calloc(256, sizeof(char *) + 3);
	arr = ft_calloc(256, sizeof(char *) + 3);
	while (value[i] != '\0')
	{
		if (value[i] == '$' && trigger == 0)
		{
			trigger = 1;
			i++;
		}
		if (value[i] == '$' && trigger == 1)
		{
			word[j++] = '\0';
			arr_str[k] = ft_strdup(word);
			k++;
			j = 0;
			trigger = 1;
			i++;
		}
		if (value[i] == ' ' || value[i] == ':')
		{
			trigger = 0;
			i++;
		}
		if (trigger == 1)
		{
			if (value[i] != '$')
			{
				word[j] = value[i];
				j++;
			}
		}
		i++;
	}
	word[j + 1] = '\0';
	arr_str[k] = ft_strdup(word);
	k++;
	arr_str[k] = NULL;
	i = 0;
	while (arr_str[i] != NULL)
	{
		printf("arr_str[%d]: %s\n", i, arr_str[i]);
		arr[i] = get_env(arr_str[i]);
		printf("arr[%d]: %s\n", i, arr[i]);
		i++;
	}
	char *result = concatenate_strings(arr);
	free_arr(arr_str);
	printf("result: %s\n", result);
	return(result);
}

int	set_env_var(t_cmds *cmds, char *key, char *value)
{
	char	**envs;
	char	*new_key;
	char	*key_and_value;
	char 	*new_value;

	printf("[set_env_var] value: %s\n", value);
	new_value = convert_values(value);
	printf("[set_env_var] new_value: %s\n", new_value);
	if (cmds->envs == NULL && cmds->current->full_args == NULL)
		return (1);
	envs = ft_calloc(count_arr(cmds->envs) + 2, sizeof(char *));
	new_key = ft_strjoin(key, "=");
	key_and_value = ft_strjoin(new_key, value);
	printf("[set_env_var] key_and_value: %s\n", key_and_value);
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

	if (cmds->envs == NULL && cmds->current->full_args == NULL)
		return (1);
	if (cmds->current->full_args == NULL)
		env_adapter(cmds);
	if (cmds->current->phrase_parsed[1] == NULL)
		return (1);
	args = ft_split(cmds->current->phrase_parsed[1], '=');
	if (args[0] == NULL || args[1] == NULL)
	{
		printf("minishell: export: `%s': not a valid identifier\n", args[0]);
		free_arr(args);
		return (1);
	}
	result = set_env_var(cmds, args[0], args[1]);
	free_arr(args);
	return (result);
}
