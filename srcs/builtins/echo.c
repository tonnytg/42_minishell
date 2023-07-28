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
			filtered_words[j] = words[i];
			j++;
		}
		i++;
	}
	return (filtered_words);
}

char	**set_echo_settings(char **words, int *settings)
{
	int		i;
	char	**filter_words;

	i = 0;
	*settings = 0;
	while (words[i] != NULL)
	{
		if (ft_strcmp(words[i], "-n") == 0)
			*settings = *settings + 1;
		if (ft_strcmp(words[i], "-e") == 0)
			*settings = *settings + 2;
		i++;
	}
	filter_words = filter_echo_words(words);
	return (filter_words);
}

int	echo_adapter(t_cmds *cmds)
{
	int		settings;
	int		exit_code;
	char	**words;
	char	**filter_words;

	if (cmds->current->full_args == NULL)
	{
		printf("\n");
		cmds->exit_code.code = 0;
		return (0);
	}
	check_quotes(cmds);
	if (cmds->has_quote)
	{
		exit_code = echo_arg_with_quotes(cmds);
		return (exit_code);
	}
	settings = 0;
	words = cmds->current->phrase_parsed;
	filter_words = set_echo_settings(words, &settings);
	exit_code = echo_exec_print(cmds, settings, filter_words);
	cmds->exit_code.code = exit_code;
	return (exit_code);
}
