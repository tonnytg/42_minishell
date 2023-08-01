/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpreter.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caalbert <caalbert@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 02:55:02 by antthoma          #+#    #+#             */
/*   Updated: 2023/06/06 10:21:31 by caalbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*parse_to_folder(char *str)
{
	char	*dir;
	char	*temp_str;
	char	*result;

	dir = getcwd(NULL, 0);
	temp_str = remove_string(str, '.');
	result = ft_strjoin(dir, temp_str);
	free(dir);
	free(temp_str);
	return (result);
}

void	parse_values_args(t_cmds *cmds)
{
	int		i;
	char	**words;

	i = 0;
	words = ft_split(cmds->current->phrase, ' ');
	cmds->current->phrase_parsed = ft_calloc(sizeof(char *),
			count_arr(words) + 1);
	while (words[i] != NULL)
	{
		if (ft_strncmp(words[i], "$", 1) == 0
			&& is_single_quote(cmds->input->datacpy) == 0)
		{
			if (ft_strncmp(words[i] + 1, "?", 1) == 0)
				cmds->current->phrase_parsed[i] = ft_itoa(cmds->exit_code.code);
			else
				cmds->current->phrase_parsed[i] = get_env(words[i]);
		}
		else if (ft_strncmp(words[i], ".", 1) == 0)
			cmds->current->phrase_parsed[i] = parse_to_folder(words[i]);
		else
			cmds->current->phrase_parsed[i] = ft_strdup(words[i]);
		i++;
	}
	free_arr(words);
}

void	prepare_phrase(t_cmds *cmds)
{
	char	**splited_phrase;
	char	**temp;
	char	*temp_str;
	char	*temp_str1;
	int		i;

	splited_phrase = ft_split(cmds->current->phrase, ' ');
	temp = ft_calloc(sizeof(char *), count_arr(splited_phrase) + 1);
	i = 0;
	while (splited_phrase[i] != NULL)
	{
		temp_str = remove_string(splited_phrase[i], '\"');
		temp[i] = remove_string(temp_str, '\'');
		free(temp_str);
		i++;
	}
	temp_str1 = concatenate_strings(temp);
	free(cmds->current->phrase);
	cmds->current->phrase = ft_strdup(temp_str1);
	free(temp_str1);
	free_arr(temp);
	free_arr(splited_phrase);
}

void	init_interpreter(t_cmds *cmds)
{
	prepare_phrase(cmds);
	parse_values_args(cmds);
}
