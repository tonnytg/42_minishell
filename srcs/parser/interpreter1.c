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

void	concate_values(t_cmds *cmds, t_parse_2	*p2)
{
	p2->var_value = getvarenv(cmds, p2->var_name);
	free(p2->var_name);
	if (p2->var_value != NULL)
	{
		ft_strlcat(p2->new_word2, p2->var_value, p2->len_total);
		p2->m += ft_strlen(p2->var_value);
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
	if (p2->word_local[p2->j] == '$'
		&& (p2->word_local[p2->j + 1] != '\0'
			&& p2->word_local[p2->j + 1] == '?'))
	{
		p2->var_name[0] = '?';
		p2->var_name[1] = '\0';
		p2->end++;
	}
	else
	{
		ft_strlcpy(p2->var_name, p2->word_local + p2->start,
			p2->end - p2->start);
		p2->var_name[p2->end - p2->start] = '\0';
	}
}

void	save_word2(t_cmds *cmds, t_parse_2	*p2)
{
	while (p2->word_local[p2->j] != '\0')
	{
		if (p2->word_local[p2->j] == '$')
		{
			get_env_from_str(p2);
			concate_values(cmds, p2);
			p2->j = p2->end;
		}
		p2->new_word2[p2->m] = p2->word_local[p2->j];
		p2->m++;
		p2->j++;
	}
	p2->new_word2[p2->m] = '\0';
}

void	create_word2(t_cmds *cmds, t_parse_2	*p2, char **words)
{
	p2->t_i = 0;
	while (words[p2->i][p2->t_i] != '\0')
	{
		p2->word_local[p2->t_i] = words[p2->i][p2->t_i];
		p2->t_i++;
	}
	p2->word_local[p2->t_i] = '\0';
	save_word2(cmds, p2);
	cmds->current->phrase_parsed[p2->i] = ft_strdup(p2->new_word2);
}

void	init_words_struct(t_parse_2 *p2, char **words)
{
	p2->len_words = ft_strlen(words[p2->i]) + 1;
	p2->len_total = p2->len_words + p2->count + 1;
	p2->word_local = ft_calloc(sizeof(char), p2->len_total + 1);
	p2->new_word2 = ft_calloc(sizeof(char), p2->len_total + 1);
	p2->new_word2[0] = '\0';
}
