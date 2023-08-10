/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpreter.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caalbert <caalbert@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 02:55:02 by antthoma          #+#    #+#             */
/*   Updated: 2023/08/09 20:27:05 by caalbert         ###   ########.fr       */
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

char	*parse_to_folder(char *str)
{
	char	*dir;
	char	*temp_str;
	char	*result;
	char	*temp_result;

	if (ft_strcmp(str, "..") == 0)
		return (ft_strdup(".."));
	dir = getcwd(NULL, 0);
	if (ft_strncmp(str, "./", 2) == 0)
	{
		temp_str = ft_strsub(str, 2, ft_strlen(str) - 2);
		result = ft_strjoin(dir, "/");
		temp_result = result;
		result = ft_strjoin(result, temp_str);
		free(temp_str);
		free(temp_result);
	}
	else
	{
		result = ft_strdup(str);
	}
	free(dir);
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
				cmds->current->phrase_parsed[i] = get_env(words[i], 1);
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
	temp_str1 = concatenate_strings(temp, 0);
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
