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
	int	i;

	i = 0;
	while (phrase[i] != '\0')
	{
		if (phrase[i] == '\"' || phrase[i] == '\'')
			return (1);
		i++;
	}
	return (0);
}

int	get_env_in_str(t_cmds *cmds, char *str)
{
	t_get_env	*t_g;
	int			count;

	t_g = ft_calloc(sizeof(t_get_env), 1);
	t_g->result = NULL;
	t_g->len_str = ft_strlen(str);
	t_g->temp_var = ft_calloc(sizeof(char), t_g->len_str + 1);
	while (str[t_g->i] != '\0')
	{
		if (str[t_g->i] == '$')
		{
			t_g->trigger = 1;
		}
		else if (t_g->trigger == 1 && str[t_g->i] == ' ')
		{
			t_g->trigger = 0;
			t_g->temp_var[t_g->j] = '\0';
			if (ft_strcmp(t_g->temp_var, "?") == 0)
			{
				t_g->result = ft_itoa(cmds->exit_code.code);
			}
			else
			{
				t_g->result = getvarenv(cmds, t_g->temp_var);
			}
			if (t_g->result == NULL || ft_strlen(t_g->result) == 0)
			{
				free(t_g->temp_var);
				return (0);
			}
			t_g->count = t_g->count + ft_strlen(t_g->result);
			if (t_g->result != NULL)
			{
				free(t_g->result);
				t_g->result = NULL;
			}
			t_g->j = 0;
		}
		else if (t_g->trigger == 1 && str[t_g->i] != ' ')
		{
			t_g->temp_var[t_g->j] = str[t_g->i];
			t_g->j++;
		}
		t_g->i++;
	}
	if (t_g->trigger == 1)
	{
		t_g->temp_var[t_g->j] = '\0';
		if (ft_strcmp(t_g->temp_var, "?") == 0)
		{
			t_g->result = ft_itoa(cmds->exit_code.code);
		}
		else
		{
			t_g->result = getvarenv(cmds, t_g->temp_var);
		}
		if (t_g->result != NULL)
			t_g->count = t_g->count + ft_strlen(t_g->result);
	}
	free(t_g->temp_var);
	if (t_g->result != NULL)
		free(t_g->result);
	count = t_g->count;
	free(t_g);
	return (count);
}

int	has_dolar(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '$')
			return (1);
		i++;
	}
	return (0);
}

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
		{
			p2->count = get_env_in_str(cmds, words[p2->i]);
		}
		p2->len_words = ft_strlen(words[p2->i]) + 1;
		p2->len_total = p2->len_words + p2->count + 1;
		p2->word_local = ft_calloc(sizeof(char), p2->len_total + 1);
		p2->new_word2 = ft_calloc(sizeof(char), p2->len_total + 1);
		p2->new_word2[0] = '\0';
		p2->t_i = 0;
		while (words[p2->i][p2->t_i] != '\0')
		{
			p2->word_local[p2->t_i] = words[p2->i][p2->t_i];
			p2->t_i++;
		}
		p2->word_local[p2->t_i] = '\0';
		while (p2->word_local[p2->j] != '\0')
		{
			if (p2->word_local[p2->j] == '$')
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
				p2->var_value = getvarenv(cmds, p2->var_name);
				free(p2->var_name);
				if (p2->var_value != NULL)
				{
					ft_strlcat(p2->new_word2, p2->var_value, p2->len_total);
					p2->m += ft_strlen(p2->var_value);
				}
				free(p2->var_value);
				p2->j = p2->end;
			}
			p2->new_word2[p2->m] = p2->word_local[p2->j];
			p2->m++;
			p2->j++;
		}
		p2->new_word2[p2->m] = '\0';
		cmds->current->phrase_parsed[p2->i] = ft_strdup(p2->new_word2);
		free(p2->new_word2);
		p2->i++;
		free(p2->word_local);
	}
	free_arr(words);
	free(p2);
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
