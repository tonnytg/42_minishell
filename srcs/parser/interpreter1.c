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

void	concatenate_values(t_cmds *cmds, t_parse_2	*p2)
{
	int	len_to_increment;

	p2->var_value = getvarenv(cmds, p2->var_name);
	free(p2->var_name);
	if (p2->var_value != NULL)
	{
		ft_strlcat(p2->new_word2, p2->var_value, p2->len_total);
		len_to_increment = ft_strlen(p2->var_value);
		p2->m += len_to_increment;
	}
	free(p2->var_value);
}

void	get_env_from_str(t_parse_2	*p2)
{
	p2->start = p2->j + 1;
	p2->end = p2->start;
	while (p2->word_local[p2->end] != '\0'
		&& (ft_isalnum(p2->word_local[p2->end])
			|| p2->word_local[p2->end] == '_'))
		p2->end++;
	p2->var_name = ft_calloc(sizeof(char), p2->end - p2->start + 2);
	if (p2->word_local[p2->j] == '$' && (p2->word_local[p2->j + 1] != '\0'
			&& p2->word_local[p2->j + 1] == '?'))
		get_dolar_env_result(p2, '?');
	else if (p2->word_local[p2->j] == '$' && (p2->word_local[p2->j + 1] != '\0'
			&& p2->word_local[p2->j + 1] == '$'))
		get_dolar_env_result(p2, '$');
	else if (p2->word_local[p2->j] == '$' && (p2->word_local[p2->j + 1] != '\0'
			&& p2->word_local[p2->j + 1] == '#'))
		get_dolar_env_result(p2, '#');
	else if (p2->word_local[p2->j] == '$' && (p2->word_local[p2->j + 1] != '\0'
			&& p2->word_local[p2->j + 1] == '*'))
		get_dolar_env_result(p2, '*');
	else
	{
		ft_strlcpy(p2->var_name, p2->word_local
			+ p2->start, p2->end - p2->start);
		p2->var_name[p2->end - p2->start] = '\0';
	}
}

void	decide_concatenate(t_cmds *cmds, t_parse_2	*p2)
{
	p2->j = 0;
	p2->m = 0;
	while (p2->word_local[p2->j] != '\0')
	{
		if ((p2->word_local[p2->j] == '$') && cmds->d_parse == 0)
		{
			get_env_from_str(p2);
			concatenate_values(cmds, p2);
			p2->j = p2->end;
		}
		p2->new_word2[p2->m] = p2->word_local[p2->j];
		p2->m++;
		p2->j++;
	}
	p2->new_word2[p2->m] = '\0';
}

void	merge_old_with_new_word(t_cmds *cmds, t_parse_2	*p2, char **words)
{
	char	*folder;

	p2->t_i = 0;
	while (words[p2->i][p2->t_i] != '\0')
	{
		p2->word_local[p2->t_i] = words[p2->i][p2->t_i];
		p2->t_i++;
	}
	p2->word_local[p2->t_i] = '\0';
	decide_concatenate(cmds, p2);
	if (ft_strncmp(p2->new_word2, ".", 1) == 0)
	{
		folder = parse_to_folder(cmds, p2->new_word2);
		cmds->current->phrase_parsed[p2->i] = ft_strdup(folder);
		free(folder);
	}
	else if (ft_strncmp(p2->new_word2, "~", 1) == 0)
	{
		folder = parse_to_folder(cmds, p2->new_word2);
		cmds->current->phrase_parsed[p2->i] = ft_strdup(folder);
		free(folder);
	}
	else
		cmds->current->phrase_parsed[p2->i] = ft_strdup(p2->new_word2);
}

void	define_size_words(t_parse_2 *p2, char **words)
{
	p2->len_words = ft_strlen(words[p2->i]) + 1;
	p2->len_total = p2->len_words + p2->count;
	p2->word_local = ft_calloc(sizeof(char *), p2->len_total);
	p2->new_word2 = ft_calloc(sizeof(char *), p2->len_total);
	p2->new_word2[0] = '\0';
}
