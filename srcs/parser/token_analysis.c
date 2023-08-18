/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_analysis.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antthoma <antthoma@student.42sp.org.br>    +#+  +:+       +#+        */
/*       calbert  <calbert@student.42sp.org.br>   +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 02:55:02 by antthoma          #+#    #+#             */
/*   Updated: 2023/04/26 00:17:13 by antthoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	concat_tk_nodes(t_cmds *cmds, t_tk_node *list_tokens)
{
	t_tk_node	*actual;
	int			i;

	actual = list_tokens;
	i = 0;
	while (actual != NULL)
	{
		actual = actual->next;
		i++;
	}
	cmds->lexical = (char **)malloc(sizeof(char *) * (i + 1));
	cmds->lexical[i] = NULL;
	actual = list_tokens;
	i = 0;
	while (actual != NULL)
	{
		cmds->lexical[i] = ft_strdup(actual->tk_type);
		actual = actual->next;
		i++;
	}
}

void	configure_trigger_quota(t_tk_analysis *t_a)
{
	if ((t_a->data_copy[t_a->i] == '\''
			|| t_a->data_copy[t_a->i] == '\"') && t_a->close_quote == 0)
		t_a->close_quote = 1;
	else if ((t_a->data_copy[t_a->i] == '\''
			|| t_a->data_copy[t_a->i] == '\"') && t_a->close_quote == 1)
		t_a->close_quote = 0;
}

void	process_token(t_tk_analysis *t_a, t_tk_node **list_tokens)
{
	t_a->new_word[t_a->j] = '\0';
	if (ft_strlen(t_a->new_word) > 0)
	{
		t_a->token = ft_strdup(t_a->new_word);
		add_tk_node(list_tokens, t_a->token, "undefined");
		free(t_a->token);
	}
	t_a->j = 0;
	t_a->skip = 1;
}

void	finalize_token(t_cmds *cmds,
		t_tk_analysis	*t_a, t_tk_node *list_tokens)
{
	process_token(t_a, &list_tokens);
	classify_tk_nodes(list_tokens);
	concat_tk_nodes(cmds, list_tokens);
	build_struct_to_exec(cmds, list_tokens);
	free(t_a->data_copy);
	free(t_a->new_word);
	free_tk_nodes(list_tokens);
	free(t_a);
}

int	token_analysis(t_cmds *cmds)
{
	t_tk_node		*list_tokens;
	t_tk_analysis	*t_a;

	t_a = ft_calloc(1, sizeof(t_tk_analysis));
	list_tokens = NULL;
	t_a->data_copy = ft_strdup(cmds->input->datacpy);
	t_a->new_word = ft_calloc(1, sizeof(char)
			* (ft_strlen(t_a->data_copy) + 1));
	while (t_a->data_copy[t_a->i] != '\0')
	{
		configure_trigger_quota(t_a);
		if (t_a->data_copy[t_a->i] == ' ' && t_a->close_quote == 0)
			process_token(t_a, &list_tokens);
		if (t_a->skip == 1)
			t_a->skip = 0;
		else
		{
			t_a->new_word[t_a->j] = t_a->data_copy[t_a->i];
			t_a->j++;
		}
		t_a->i++;
	}
	finalize_token(cmds, t_a, list_tokens);
	return (1);
}
