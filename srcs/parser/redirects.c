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
//
//int	init_redirects(t_cmd *cmd_node)
//{
//	exec_redirect(cmd_node);
//	if ((g_data.mns).exit_code == 0)
//		dup2(cmd_node->fd_in, STDIN_FILENO);
//	if ((g_data.mns).exit_code == 1)
//	{
//		if (cmd_node->fd_in < 0 || cmd_node->fd_out < 0)
//		{
//			if (cmd_node->next != NULL)
//			{
//				dup2(g_data.exec.fd[0], STDIN_FILENO);
//				close (g_data.exec.fd[0]);
//				close (g_data.exec.fd[1]);
//				return (0);
//			}
//			else
//				return (1);
//		}
//	}
//	return (0);
//}
//
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
