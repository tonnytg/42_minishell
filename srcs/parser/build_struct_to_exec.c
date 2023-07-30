/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_struct_to_exec.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antthoma <antthoma@student.42sp.org.br>    +#+  +:+       +#+        */
/*       calbert  <calbert@student.42sp.org.br>   +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 02:55:02 by antthoma          #+#    #+#             */
/*   Updated: 2023/06/18 00:17:13 by antthoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_cmd_nodes(t_cmd_node *list_cmds)
{
	t_cmd_node	*temp;

	while (list_cmds != NULL)
	{
		temp = list_cmds;
		list_cmds = list_cmds->next;
		if (temp->phrase != NULL)
			free(temp->phrase);
		if (temp->phrase_temp != NULL)
			free(temp->phrase_temp);
		if (temp->type != NULL)
			free(temp->type);
		if (temp != NULL)
			free(temp);
	}
}

void	new_node_cmd(t_cmd_node **head, char *str, char *type)
{
	t_cmd_node	*actual;
	t_cmd_node	*new_cmd;

	actual = *head;
	new_cmd = ft_calloc(1, sizeof(t_cmd_node));
	new_cmd->phrase = ft_strdup(str);
	new_cmd->phrase_temp = ft_strdup(str);
	new_cmd->type = ft_strdup(type);
	new_cmd->next = NULL;
	new_cmd->prev = actual;
	if (*head == NULL)
		*head = new_cmd;
	else
	{
		actual = *head;
		while (actual->next != NULL)
			actual = actual->next;
		actual->next = new_cmd;
	}
}

char	*copy_if_firstword(int *firstword2, char *str, t_tk_node *actual_tk)
{
	int		first_word;
	char	*temp;

	first_word = *firstword2;
	if (!first_word)
	{
		temp = str;
		str = ft_strjoin(temp, " ");
		free(temp);
	}
	temp = str;
	str = ft_strjoin(temp, actual_tk->token);
	free(temp);
	first_word = 0;
	*firstword2 = first_word;
	return (str);
}

char	*create_cmd_nodes(t_cmd_node **list_cmds, t_tk_node **list_tokens)
{
	t_tk_node	*actual_tk;
	char		*temp;
	int			first_word;
	char		*str;

	first_word = 1;
	str = ft_strdup("");
	actual_tk = *list_tokens;
	while (actual_tk != NULL)
	{
		if (ft_strcmp(actual_tk->tk_type, "WORD") == 0)
			str = copy_if_firstword(&first_word, str, actual_tk);
		else
		{
			temp = str;
			new_node_cmd(list_cmds, temp, "WORD");
			if (actual_tk->next != NULL)
				new_node_cmd(list_cmds, " ", actual_tk->tk_type);
			str = ft_strdup("");
			free(temp);
			first_word = 1;
		}
		actual_tk = actual_tk->next;
	}
	return (str);
}

void	build_struct_to_exec(t_cmds *cmds, t_tk_node *list_tokens)
{
	t_cmd_node	*list_cmds;
	t_cmd_node	*actual;
	char		*str;

	list_cmds = NULL;
	str = create_cmd_nodes(&list_cmds, &list_tokens);
	if (list_cmds == NULL && list_tokens != NULL)
		new_node_cmd(&list_cmds, str, "WORD");
	actual = list_cmds;
	while (actual->next != NULL)
		actual = actual->next;
	if (list_cmds != NULL && ft_strcmp(actual->type, "WORD") != 0)
		new_node_cmd(&list_cmds, str, "WORD");
	free(str);
	cmds->cmd_list = list_cmds;
}
