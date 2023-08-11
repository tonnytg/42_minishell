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

void	check_quote(char *word, t_cmd_build *cmds)
{
	int	i;

	i = 0;
	while (word[i] != '\0')
	{
		if (word[i] == '\"')
		{
			if (cmds->has_quote == 0)
			{
				cmds->has_quote = 1;
				return ;
			}
			else
			{
				cmds->has_quote = 0;
				return ;
			}
		}
		i++;
	}
}
