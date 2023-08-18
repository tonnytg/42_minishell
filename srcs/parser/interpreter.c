/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpreter.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caalbert <caalbert@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 02:55:02 by antthoma          #+#    #+#             */
/*   Updated: 2023/08/11 00:50:37 by caalbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char	*substring;
	size_t	i;

	if (!s)
		return (NULL);
	substring = (char *)malloc(sizeof(char) * (len + 1));
	if (!substring)
		return (NULL);
	i = 0;
	while (i < len && s[start + i])
	{
		substring[i] = s[start + i];
		i++;
	}
	substring[i] = '\0';
	return (substring);
}

int	check_quote_phrase(char *phrase)
{
	int	i = 0;

	while (phrase[i] != '\0')
	{
		if (phrase[i] == '\"' || phrase[i] == '\'')
			return (1);
		i++;
	}
	return (0);
}

int	get_env_in_str(t_cmds *cmds, char *str)
{
	int i = 0;
	int j = 0;
	int count = 0;
	int trigger = 0;
	char *temp_var;
	char *result;

	result = NULL;
	int len_str = ft_strlen(str);
	temp_var = ft_calloc(sizeof(char), len_str + 1);
	while (str[i] != '\0')
	{
		if (str[i] == '$')
		{
			trigger = 1;
		}
		else if (trigger == 1 && str[i] == ' ')
		{
			trigger = 0;
			temp_var[j] = '\0';
			if (ft_strcmp(temp_var, "?") == 0)
			{
				result = ft_itoa(cmds->exit_code.code);
			}
			else
			{
				result = getvarenv(cmds, temp_var);
			}
			if (result == NULL || ft_strlen(result) == 0)
			{
				free(temp_var);
				return (0);
			}
			// echo "Ola $NAME voce esta em $PWD mas mora em $HOME, o result foi $?"
			count =  count + ft_strlen(result);
			if (result != NULL)
			{
				free(result);
				result = NULL;
			}
			j = 0;
		}
		else if (trigger == 1 && str[i] != ' ')
		{
			temp_var[j] = str[i];
			j++;
		}
		i++;
	}
	if (trigger == 1)
	{
		temp_var[j] = '\0';
		if (ft_strcmp(temp_var, "?") == 0)
		{
			result = ft_itoa(cmds->exit_code.code);
		}
		else
		{
			result = getvarenv(cmds, temp_var);
		}
		if (result != NULL)
			count =  count + ft_strlen(result);
	}
	free(temp_var);
	if (result != NULL)
		free(result);
	return (count);
}

int has_dolar(char *str)
{
	int i = 0;

	while (str[i] != '\0')
	{
		if (str[i] == '$')
			return (1);
		i++;
	}
	return (0);
}

void	parse_values_args(t_cmds *cmds)
{
	int		i;
	char	**words;

	int result = check_quote_phrase(cmds->current->phrase);
	if (result == 1)
	{
		char *new_word;
		new_word = ft_calloc(sizeof(char), ft_strlen(cmds->current->phrase) + 1);
		words = ft_calloc(sizeof(char *) , 3);
		int k = 0;
		i = 0;
		int j = 0;
		while (cmds->current->phrase[i] != '\0')
		{
			if (cmds->current->phrase[i] == ' ')
			{
				new_word[j] = '\0';
				i++;
				break ;
			}
			if (cmds->current->phrase[i] == '\"' || cmds->current->phrase[i] == '\'')
			{
				i++;
			}
			else
			{
				new_word[j] = cmds->current->phrase[i];
				j++;
				i++;
			}
		}
		words[k] = ft_strdup(new_word);
		free(new_word);
		k++;
		j = 0;
		char *new_word3;
		new_word3 = ft_calloc(sizeof(char), ft_strlen(cmds->current->phrase) + 1);
		while (cmds->current->phrase[i] != '\0')
		{
			if (cmds->current->phrase[i] == '\"' || cmds->current->phrase[i] == '\'')
			{
				i++;
			}
			else
			{
				new_word3[j] = cmds->current->phrase[i];
				j++;
				i++;
			}
		}
		new_word3[j] = '\0';
		words[k] = ft_strdup(new_word3);
		k++;
		words[k] = NULL;
		free(new_word3);
	}
	else
	{
		words = ft_split(cmds->current->phrase, ' ');
	}
	cmds->current->phrase_parsed = ft_calloc(sizeof(char *), count_arr(words) + 1);
	i = 0;
	while (words[i] != NULL)
	{
		int j = 0;
		int m = 0;
		char *word_local;
		int count = 0;

		if (has_dolar(words[i]))
			count = get_env_in_str(cmds, words[i]);
		int len_words = ft_strlen(words[i]) + 1;
		int len_total = len_words  + count + 1;

		word_local = ft_calloc(sizeof(char), len_total + 1);
		char *new_word2;
		new_word2 = ft_calloc(sizeof(char), len_total + 1);
		new_word2[0] = '\0';
		int t_i = 0;
		while (words[i][t_i] != '\0')
		{
			word_local[t_i] = words[i][t_i];
			t_i++;
		}
		word_local[t_i] = '\0';
		while (word_local[j] != '\0')
		{
			if (word_local[j] == '$')
			{
				int start = j + 1;
				int end = start;
				while (word_local[end] != '\0' && (ft_isalnum(word_local[end]) || word_local[end] == '_')) {
					end++;
				}
				char var_name[end - start + 1];
				if (word_local[j] == '$' && (word_local[j + 1] != '\0' && word_local[j + 1] == '?'))
				{
					var_name[0] = '?';
					var_name[1] = '\0';
					end++;
				}
				else
				{
					ft_strlcpy(var_name, word_local + start, end - start);
					var_name[end - start] = '\0';
				}
				char *var_value = getvarenv(cmds, var_name);
				if (var_value != NULL)
				{
					ft_strlcat(new_word2, var_value, len_total);
					m += ft_strlen(var_value);
				}
				free(var_value);
				j = end;
			}
			new_word2[m] = word_local[j];
			m++;
			j++;
		}
		new_word2[m] = '\0';
		cmds->current->phrase_parsed[i] = ft_strdup(new_word2);
		free(new_word2);
		i++;
		free(word_local);
	}
	free_arr(words);
}

void	init_interpreter(t_cmds *cmds)
{
	parse_values_args(cmds);
}
