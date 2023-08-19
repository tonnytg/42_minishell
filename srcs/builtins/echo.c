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

char	**filter_echo_words(char **words)
{
	char	**filtered_words;
	int		i;
	int		j;
	int		count;

	j = 0;
	count = count_words_echo(words);
	filtered_words = ft_calloc(count + 1, sizeof(char *));
	i = 1;
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

	i = 1;
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

void	replace_escape_chars(char *str)
{
	char	*src;
	char	*dest;

	src = str;
	dest = str;
	while (*src)
	{
		if (*src == '\\')
		{
			src++;
			if (*src == 'n')
				*dest = '\n';
			else if (*src == 't')
				*dest = '\t';
			else
				*dest = *src;
		}
		else
			*dest = *src;
		src++;
		dest++;
	}
	*dest = '\0';
}

int	echo_print(t_cmds *cmds, char **words, int *settings)
{
	int	i;

	if (words == NULL)
	{
		write(STDOUT_FILENO, "\n", 1);
		return (0);
	}
	i = 0;
	cmds->d_parse = 0;
	while (words[i] != NULL)
	{
		if (((*settings == 2) || (*settings == 3)) && cmds->d_parse == 0)
			replace_escape_chars(words[i]);
		write(STDOUT_FILENO, words[i], ft_strlen(words[i]));
		if (words[i + 1] != NULL)
			write(STDOUT_FILENO, " ", 1);
		i++;
	}
	if ((*settings % 2) == 0)
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
	exit_code = echo_print(cmds, words, &settings);
	free_arr(words);
	cmds->exit_code.code = exit_code;
	return (exit_code);
}
