/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c.                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antthoma <antthoma@student.42sp.org.br>    +#+  +:+       +#+        */
/*       calbert  <calbert@student.42sp.org.br>   +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 02:55:02 by antthoma          #+#    #+#             */
/*   Updated: 2023/04/26 00:17:13 by antthoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	count_words(char **words)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (words[i] != NULL)
	{
		if (ft_strcmp(words[i], "-n") != 0 && ft_strcmp(words[i], "-e") != 0)
			count++;
		i++;
	}
	return (count);
}

char	**filter_echo_words(char **words)
{
	char	**filtered_words;
	int		i;
	int		j;
	int		count;

	j = 0;
	count = count_words(words);
	filtered_words = ft_calloc(count + 1, sizeof(char *));
	i = 0;
	while (words[i] != NULL)
	{
		if (ft_strcmp(words[i], "-n") != 0 && ft_strcmp(words[i], "-e") != 0)
		{
			filtered_words[j] = ft_strdup(words[i]);
			j++;
		}
		i++;
	}
	return (filtered_words);
}

char	**set_echo_settings(t_cmds *cmds, int *settings)
{
	int		i;
	char	**filter_words;

	i = 0;
	*settings = 0;
	if (cmds->current->phrase_parsed == NULL)
		return (NULL);
	while (cmds->current->phrase_parsed[i] != NULL)
	{
		if (ft_strcmp(cmds->current->phrase_parsed[i], "-n") == 0)
			*settings = *settings + 1;
		if (ft_strcmp(cmds->current->phrase_parsed[i], "-e") == 0)
			*settings = *settings + 2;
		i++;
	}
	filter_words = filter_echo_words(cmds->current->phrase_parsed);
	return (filter_words);
}

int	echo_print(char **words, int *settings)
{
	int	i;

	i = 0;
	if (words == NULL)
	{
		write(STDOUT_FILENO, "\n", 1);
		return (0);
	}
	while (words[i] != NULL)
	{
		write(STDOUT_FILENO, words[i], ft_strlen(words[i]));
		if (words[i + 1] != NULL)
			write(STDOUT_FILENO, " ", 1);
		i++;
	}
	if (*settings == 0)
		write(STDOUT_FILENO, "\n", 1);
	return (0);
}

int	echo_adapter(t_cmds *cmds)
{
	int		exit_code;
	int		settings;
	char	**words;

	if (cmds->current->full_args == NULL)
	{
		write(STDOUT_FILENO, "\n", 1);
		return (0);
	}
	words = set_echo_settings(cmds, &settings);
	exit_code = echo_print(words, &settings);
	free_arr(words);
	return (exit_code);
}
