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

void	build_struct_to_exec(t_cmds *cmds, t_tk_node *list_tokens)
{
	t_tk_node	*actual;

	actual = list_tokens;
	while (actual != NULL)
	{
		if (ft_strcmp(actual->tk_type, "WORD") == 0)
		{
			printf("WORD: %s\n", actual->token);
			printf("cmds data %s\n", cmds->input->data);
			actual = actual->next;
		}
		else
			actual = actual->next;
	}
}
