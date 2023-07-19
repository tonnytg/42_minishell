/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.c 			                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antthoma <antthoma@student.42sp.org.br>    +#+  +:+       +#+        */
/*       calbert  <calbert@student.42sp.org.br>   +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 02:55:02 by antthoma          #+#    #+#             */
/*   Updated: 2023/06/18 00:17:13 by antthoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	check_exist_redirect(t_cmds *cmds)
{
	t_cmd_node	*actual;

	cmds->redirects_count = 0;
	actual = cmds->cmd_list;
	while (actual != NULL)
	{
		if (ft_strcmp(actual->type, "LESS") == 0)
			cmds->redirects_count++;
		if (ft_strcmp(actual->type, "DLESS") == 0)
			cmds->redirects_count++;
		if (ft_strcmp(actual->type, "GREAT") == 0)
			cmds->redirects_count++;
		if (ft_strcmp(actual->type, "DGREAT") == 0)
			cmds->redirects_count++;
		actual = actual->next;
	}
}
