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
	int i = 0;
	int r = 0;
	int w = 0;
	int a = 0;
	int trigger = 0;
	int rest_active = 0;
	char *converted;
	char rest[256];
	char word[256];
	char **arr;

	arr = ft_calloc(256, sizeof(char *) + 5);
	while (value[i] != '\0') // export PATH=$HOME:$PATH:/opt
	{
		if (value[i] == '$')
		{
			if (rest_active == 1)
			{
				rest_active = 0;
				rest[r] = '\0';
				printf("[1] - rest: %s\n", rest);
				arr[a] = ft_strdup(rest);
				a++;
				r = 0;
			}
			trigger = 1;
			printf("trigger activated\n");
			i++;
		}
		if (trigger == 1 && (value[i] == ':' || value[i] == ' '))
		{
			trigger = 0;
			printf("trigger deactivated\n");
			word[w] = '\0';
			printf("[1] - word: %s\n", word);
			converted = get_env(word, 0);
			if (converted != NULL)
			{
				printf("[1] - converted - '%s'\n", converted);
				arr[a] = ft_strdup(converted);
				a++;
			}
			free(converted);
			w = 0;
		}
		if (trigger == 1)
		{
			printf("[1] - word letter: %c\n", value[i]);
			word[w] = value[i];
			w++;
		}
		if (trigger == 0 && value[i] != '$')
		{
			if (value[i] != ':')
			{
				rest_active = 1;
				printf("[2] - rest letter: %c\n", value[i]);
				rest[r] = value[i];
				r++;
			}
			else if (value[i] == ':' && rest_active == 1)
			{
				rest_active = 0;
				rest[r] = '\0';
				printf("[2] - rest: %s\n", rest);
				arr[a] = ft_strdup(rest);
				a++;
				r = 0;
			}
		}
		i++;
	}
	if (rest_active == 1)
	{
		rest_active = 0;
		rest[r] = '\0';
		printf("[2] - rest: %s\n", rest);
		arr[a] = ft_strdup(rest);
		a++;
		r = 0;
	}

	if (trigger == 1)
	{
		trigger = 0;
		printf("trigger deactivated\n");
		word[w] = '\0';
		printf("[1] - word: %s\n", word);
		converted = get_env(word, 0);
		if (converted != NULL)
		{
			printf("[1] - converted - '%s'\n", converted);
			arr[a] = ft_strdup(converted);
			a++;
		}
		w = 0;
	}
	arr[a] = NULL;

	i = 0;
	while (arr[i] != NULL)
	{
		printf("arr[%d]: '%s'\n", i, arr[i]);
		i++;
	}

	char *converted_arr = concatenate_strings(arr, ':');
	printf("converted_arr: '%s'\n", converted_arr);
	free_arr(arr);
	return(converted_arr);
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
	key_and_value = ft_strjoin(new_key, new_value);
	free(new_value);
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
