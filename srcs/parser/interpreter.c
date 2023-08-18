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

void	parse_values_args(t_cmds *cmds)
{
	int		i;
	char	**words;

	int result = check_quote_phrase(cmds->current->phrase);
	if (result == 1)
	{
		char *new_word;
		new_word = malloc(sizeof(char) * 2);
		words = malloc(sizeof(char *) * 2);
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
		k++;
		j = 0;
		while (cmds->current->phrase[i] != '\0')
		{
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
		new_word[j] = '\0';
		words[k] = ft_strdup(new_word);
		k++;
		words[k] = NULL;
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
		printf("\n");
		printf("[parse_values_args] - word: '%s'\n", words[i]);
		char *new_word;
		new_word = malloc(sizeof(char) * 100);
		while (words[i][j] != '\0')
		{
			if (words[i][j] == '$')
			{
				int start = j + 1;
				int end = start;
				while (words[i][end] != '\0' && (isalnum(words[i][end]) || words[i][end] == '_')) {
					end++;
				}

				// Extract the variable name
				char var_name[end - start + 1];
				strncpy(var_name, words[i] + start, end - start);
				var_name[end - start] = '\0';

				// Get the environment variable value
				char *var_value = getenv(var_name);
				if (var_value != NULL) {
					strcat(new_word, var_value);
					m += strlen(var_value);
				}

				j = end; // Move j to the end of the variable name

			}
			printf("[parse_values_args] - word[%d][%d]: '%c'\n", i, j, words[i][j]);
			new_word[m] = words[i][j];
			m++;
			j++;
		}
		new_word[m] = '\0';
		cmds->current->phrase_parsed[i] = ft_strdup(new_word);
		printf("[parse_values_args] - new_word: '%s'\n", new_word);
		i++;
	}
}

void	init_interpreter(t_cmds *cmds)
{
	parse_values_args(cmds);
}
