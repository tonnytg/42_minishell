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
		free(temp->phrase);
		free(temp->type);
		free(temp);
	}
}

void	new_node_cmd(t_cmd_node **head, char *str, char *type)
{
	t_cmd_node	*actual;
	t_cmd_node	*new_cmd;

	actual = *head;
	new_cmd = (t_cmd_node *)malloc(sizeof(t_cmd_node));
	new_cmd->phrase = ft_strdup(str);
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

void	build_struct_to_exec(t_cmds *cmds, t_tk_node *list_tokens)
{
	t_cmd_node	*list_cmds;
	t_cmd_node	*actual;
	t_tk_node	*actual_tk;
	char		*str;
	char		*temp;

	str = ft_strdup("");
	list_cmds = NULL;
	actual_tk = list_tokens;
	while (actual_tk != NULL)
	{
		if (ft_strcmp(actual_tk->tk_type, "WORD") == 0)
		{
			temp = str;
			str = ft_strjoin(temp, actual_tk->token);
			free(temp);
			temp = str;
			str = ft_strjoin(temp, " ");
			free(temp);
		}
		if (ft_strcmp(actual_tk->tk_type, "WORD") != 0)
		{
			char *temp_str = str;
			new_node_cmd(&list_cmds, temp_str, "WORD");
			new_node_cmd(&list_cmds, " ", actual_tk->tk_type);
			str = ft_strdup(""); // Reinicializa a variável str
			free(temp_str); // Libera a memória apenas uma vez
		}
		actual_tk = actual_tk->next;
	}
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
