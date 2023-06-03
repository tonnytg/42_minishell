/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antthoma <antthoma@student.42sp.org.br>    +#+  +:+       +#+        */
/*       calbert  <calbert@student.42sp.org.br>   +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 02:55:02 by antthoma          #+#    #+#             */
/*   Updated: 2023/04/26 00:17:13 by antthoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	find_command(t_cmds *cmds)
{
	int	i;

	i = 0;
	while (i < cmds->num_cmds && cmds->input->cmd_name != NULL)
	{
		if (ft_strcmp(cmds->arr_cmds[i].name, cmds->input->cmd_name) == 0)
		{
			ft_memcpy(cmds->cmd_finded, &cmds->arr_cmds[i], sizeof(t_command));
			return ;
		}
		i++;
	}
	ft_printf("minishell: %s: command not found\n", cmds->input->cmd_name);
	cmds->cmd_finded->name = NULL;
}

void	read_keyboard(t_cmds *cmds)
{
	ft_printf("> ");
	fgets(cmds->input->data, sizeof(cmds->input->data), stdin);
	cmds->input->data[strcspn(cmds->input->data, "\n")] = 0;
	cmds->input->cmd_name = ft_strtok(cmds->input->data, " ", 1);
	cmds->input->cmd_args = ft_strtok(NULL, "", 0);
}
