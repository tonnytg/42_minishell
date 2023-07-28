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
		free(temp->phrase_temp);
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
	printf("[1 new_node_cmd] - vou salvar: '%s'\n", str);
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

void	create_cmd_nodes(t_cmd_node **list_cmds, // TODO: Tem uma falha aqui "echo a b" vira "echo a b "
	t_tk_node **list_tokens, char *str)
{
	t_tk_node	*actual_tk;
	char		*temp;

	actual_tk = *list_tokens;
	while (actual_tk != NULL)
	{
		if (ft_strcmp(actual_tk->tk_type, "WORD") == 0)
		{
			temp = str;
			str = ft_strjoin(temp, actual_tk->token);
			free(temp);
			temp = str;
			printf("[1] - vou salvar: '%s'\n", str);
			str = ft_strjoin(temp, " ");
			free(temp);
		}
		if (ft_strcmp(actual_tk->tk_type, "WORD") != 0)
		{
			printf("[2] - vou salvar: '%s'\n", str);
			temp = str;
			new_node_cmd(list_cmds, temp, "WORD");
			if (actual_tk->next != NULL)
				new_node_cmd(list_cmds, " ", actual_tk->tk_type);
			str = ft_strdup("");
			free(temp);
		}
		actual_tk = actual_tk->next;
	}

	// TODO: Problema está aqui!

	t_cmd_node *actual1;
	actual1 = *list_cmds;
	while (actual1 != NULL)
	{
		printf("[11 t_cmd_node]'%s' - '%s'\n", actual1->phrase, actual1->type);
		actual1 = actual1->next;
	}

	t_tk_node *actual2;
	actual2 = *list_tokens;
	while (actual2 != NULL)
	{
		printf("[22 t_tk_node]'%s' - '%s'\n", actual2->token, actual2->tk_type);
		actual2 = actual2->next;
	}


}

void	build_struct_to_exec(t_cmds *cmds, t_tk_node *list_tokens)
{
	t_cmd_node	*list_cmds;
	t_cmd_node	*actual;
	char		*str;

	str = ft_strdup("");
	list_cmds = NULL;
	create_cmd_nodes(&list_cmds, &list_tokens, str);
	if (list_cmds == NULL && list_tokens != NULL)
	{

		new_node_cmd(&list_cmds, str, "WORD");
		printf("[1 build_struct_to_exec] - vou salvar: '%s'\n", str);
	}

	// print all elements list_cmds
	t_cmd_node *actual1;
	actual1 = list_cmds;
	while (actual1 != NULL)
	{
		printf("[1 build_struct_to_exec]'%s' - '%s'\n", actual1->phrase, actual1->type);
		actual1 = actual1->next;
	}



	actual = list_cmds;
	while (actual->next != NULL)
		actual = actual->next;
	if (list_cmds != NULL && ft_strcmp(actual->type, "WORD") != 0)
		new_node_cmd(&list_cmds, str, "WORD");
	t_cmd_node *actual2;
	actual2 = list_cmds;
	while (actual2 != NULL)
	{
		printf("[2 build_struct_to_exec]'%s' - '%s'\n", actual2->phrase, actual2->type);
		actual2 = actual2->next;
	}
	printf("str: %s\n", str);
	free(str);
	cmds->cmd_list = list_cmds;
}
