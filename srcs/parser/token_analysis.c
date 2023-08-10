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

void	add_tk_node(t_tk_node **head, char *token, char *tk_type)
{
	t_tk_node	*new_token;
	t_tk_node	*actual;

	new_token = ft_calloc(1, sizeof(t_tk_node));
	strcpy(new_token->token, token);
	strcpy(new_token->tk_type, tk_type);
	new_token->next = NULL;
	if (*head == NULL)
		*head = new_token;
	else
	{
		actual = *head;
		while (actual->next != NULL)
			actual = actual->next;
		actual->next = new_token;
	}
}

void	free_tk_nodes(t_tk_node *list_tokens)
{
	t_tk_node	*temp;

	while (list_tokens != NULL)
	{
		temp = list_tokens;
		list_tokens = list_tokens->next;
		free(temp);
	}
}

void	classify_tk_nodes(t_tk_node *list_tokens)
{
	t_tk_node	*actual;

	actual = list_tokens;
	while (actual != NULL)
	{
		if (strcmp(actual->token, "|") == 0)
			ft_strlcpy(actual->tk_type, "PIPE", 5);
		else if (strcmp(actual->token, "<") == 0)
			ft_strlcpy(actual->tk_type, "LESS", 5);
		else if (strcmp(actual->token, "<<") == 0)
			ft_strlcpy(actual->tk_type, "DLESS", 6);
		else if (strcmp(actual->token, ">") == 0)
			ft_strlcpy(actual->tk_type, "GREAT", 6);
		else if (strcmp(actual->token, ">>") == 0)
			ft_strlcpy(actual->tk_type, "DGREAT", 7);
		else
			ft_strlcpy(actual->tk_type, "WORD", 5);
		actual = actual->next;
	}
}

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

int	token_analysis(t_cmds *cmds)
{
	char		*token;
	char		*data_copy;
	t_tk_node	*list_tokens;

	list_tokens = NULL;
	data_copy = ft_strdup(cmds->input->datacpy);
	token = ft_strtok(data_copy, " ", 1);
	while (token != NULL)
	{
		add_tk_node(&list_tokens, token, "undefined");
		token = ft_strtok(NULL, " ", 0);
	}
	classify_tk_nodes(list_tokens);
	concat_tk_nodes(cmds, list_tokens);
	build_struct_to_exec(cmds, list_tokens);
	free_tk_nodes(list_tokens);
	free(data_copy);
	return (1);
}
