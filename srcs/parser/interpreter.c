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

void	parse_values_args2(t_cmds *cmds, char **words)
{
	t_parse_2	*p2;

	p2 = ft_calloc(sizeof(t_parse_2), 1);
	cmds->current->phrase_parsed = ft_calloc(
			sizeof(char *), count_arr(words) + 1);
	p2->i = 0;
	while (words[p2->i] != NULL)
	{
		p2->j = 0;
		p2->m = 0;
		p2->count = 0;
		if (has_dolar(words[p2->i]))
			p2->count = get_env_in_str(cmds, words[p2->i]);
		init_words_struct(p2, words);
		create_word2(cmds, p2, words);
		free(p2->new_word2);
		p2->i++;
		free(p2->word_local);
	}
	free_arr(words);
	free(p2);
}

void	p1_build_word3(t_cmds *cmds, t_parse_1 *p1)
{
	p1->j = 0;
	p1->new_word3 = ft_calloc(sizeof(char),
			ft_strlen(cmds->current->phrase) + 1);
	while (cmds->current->phrase[p1->i] != '\0')
	{
		if (cmds->current->phrase[p1->i] == '\"'
			|| cmds->current->phrase[p1->i] == '\'')
			p1->i++;
		else
		{
			p1->new_word3[p1->j] = cmds->current->phrase[p1->i];
			p1->j++;
			p1->i++;
		}
	}
	p1->new_word3[p1->j] = '\0';
}

void	build_new_word(t_cmds *cmds, t_parse_1 *p1)
{
	while (cmds->current->phrase[p1->i] != '\0')
	{
		if (cmds->current->phrase[p1->i] == ' ')
		{
			p1->new_word[p1->j] = '\0';
			p1->i++;
			break ;
		}
		if (cmds->current->phrase[p1->i] == '\"'
			|| cmds->current->phrase[p1->i] == '\'')
			p1->i++;
		else
		{
			p1->new_word[p1->j] = cmds->current->phrase[p1->i];
			p1->j++;
			p1->i++;
		}
	}
	p1->words[p1->k] = ft_strdup(p1->new_word);
	free(p1->new_word);
	p1->k++;
}

void	parse_values_args(t_cmds *cmds)
{
	t_parse_1	*p1;

	p1 = ft_calloc(sizeof(t_parse_1), 1);
	p1->result = check_quote_phrase(cmds->current->phrase);
	if (p1->result == 1)
	{
		p1->new_word = ft_calloc(sizeof(char),
				ft_strlen(cmds->current->phrase) + 1);
		p1->words = ft_calloc(sizeof(char *), 3);
		p1->k = 0;
		p1->j = 0;
		build_new_word(cmds, p1);
		p1_build_word3(cmds, p1);
		p1->words[p1->k] = ft_strdup(p1->new_word3);
		p1->k++;
		p1->words[p1->k] = NULL;
		free(p1->new_word3);
	}
	else
		p1->words = ft_split(cmds->current->phrase, ' ');
	parse_values_args2(cmds, p1->words);
	free(p1);
}

void	init_interpreter(t_cmds *cmds)
{
	parse_values_args(cmds);
}
