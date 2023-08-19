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

void	convert_env_to_str(t_cmds *cmds, char **words)
{
	t_parse_2	*p2;

	p2 = ft_calloc(sizeof(t_parse_2), 1);
	cmds->current->phrase_parsed = ft_calloc(
			sizeof(char *), count_arr(words) + 1);
	p2->i = 0;
	while (words[p2->i] != NULL)
	{
		if (has_dolar(words[p2->i]))
			p2->count = count_all_envs_in_str(cmds, words[p2->i]);
		define_size_words(p2, words);
		merge_old_with_new_word(cmds, p2, words);
		free(p2->new_word2);
		free(p2->word_local);
		p2->i++;
	}
	free_arr(words);
	free(p2);
}

void	build_args(t_cmds *cmds, t_parse_1 *p1)
{
	int		i;
	char	*word;

	i = 0;
	word = ft_calloc(sizeof(char), ft_strlen(cmds->current->phrase) + 1);
	while (cmds->current->phrase[p1->i] != '\0')
	{
		if (cmds->current->phrase[p1->i] == ' ')
		{
			word[i] = '\0';
			p1->words[p1->k] = ft_strdup(word);
			printf("[build_args] - [%d]words: '%s'\n", p1->k, p1->words[p1->k]);
			p1->k++;
			p1->i++;
			i = 0;
		}
		word[i] = cmds->current->phrase[p1->i];
		i++;
		p1->i++;
	}
	word[i] = '\0';
	p1->words[p1->k] = ft_strdup(word);
	printf("[build_args] - [%d]words: '%s'\n", p1->k, p1->words[p1->k]);
}

void	build_command_name(t_cmds *cmds, t_parse_1 *p1)
{
	int i;

	i = 0;
	while (cmds->current->phrase[p1->i] != '\0')
	{
		if (cmds->current->phrase[p1->i] == ' ')
		{
			p1->command_name[i] = '\0';
			p1->i++;
			break ;
		}
		if (cmds->current->phrase[p1->i] == '\"'
			|| cmds->current->phrase[p1->i] == '\'')
			p1->i++;
		p1->command_name[i] = cmds->current->phrase[p1->i];
		i++;
		p1->i++;
	}
	p1->words[p1->k] = ft_strdup(p1->command_name);
	free(p1->command_name);
	p1->k++;
}

void	decide_split_or_not(t_cmds *cmds)
{
	t_parse_1	*p1;

	p1 = ft_calloc(sizeof(t_parse_1), 1);
	p1->result = check_quote_phrase(cmds->current->phrase);
	if (p1->result == 1)
	{
		p1->command_name = ft_calloc(sizeof(char),
				ft_strlen(cmds->current->phrase) + 1);
		p1->words = ft_calloc(sizeof(char *), 10);
		build_command_name(cmds, p1);
		build_args(cmds, p1);
	}
	else
		p1->words = ft_split(cmds->current->phrase, ' ');
	convert_env_to_str(cmds, p1->words);
	free(p1);
}

void	init_interpreter(t_cmds *cmds)
{
	printf("[init_interpreter] - phrase: '%s'\n", cmds->current->phrase);
	decide_split_or_not(cmds);
}
