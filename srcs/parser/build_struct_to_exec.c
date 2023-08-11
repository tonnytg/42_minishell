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
	if (*head == NULL)
	{
		new_cmd->prev = NULL;
		*head = new_cmd;
	}
	else
	{
		while (actual->next != NULL)
		{
			actual = actual->next;
		}
		actual->next = new_cmd;
		new_cmd->prev = actual;
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

void	save_node_cmd(t_cmd_node **list_cmds, t_cmd_build	*cmds)
{
	cmds->temp = cmds->str;
	new_node_cmd(list_cmds, cmds->temp, "WORD");
	if (cmds->actual_tk->next != NULL)
		new_node_cmd(list_cmds, " ", cmds->actual_tk->tk_type);
	cmds->str = ft_strdup("");
	free(cmds->temp);
	cmds->first_word = 1;
}

char	*create_cmd_nodes(t_cmd_node **list_cmds, t_tk_node **list_tokens)
{
	t_cmd_build	*cmds;
	char		*str;

	cmds = ft_calloc(1, sizeof(t_cmd_build));
	cmds->first_word = 1;
	cmds->str = ft_strdup("");
	cmds->actual_tk = *list_tokens;
	while (cmds->actual_tk != NULL)
	{
		check_quote(cmds->actual_tk->token, cmds);
		if (ft_strcmp(cmds->actual_tk->tk_type, "WORD") == 0
			|| cmds->has_quote == 1)
			cmds->str = copy_if_firstword(
					&cmds->first_word, cmds->str, cmds->actual_tk);
		else
			save_node_cmd(list_cmds, cmds);
		cmds->actual_tk = cmds->actual_tk->next;
	}
	str = ft_strdup(cmds->str);
	free(cmds->str);
	free(cmds);
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
