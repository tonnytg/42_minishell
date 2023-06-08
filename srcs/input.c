/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caalbert <caalbert@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 02:55:02 by antthoma          #+#    #+#             */
/*   Updated: 2023/06/03 22:56:19 by caalbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	find_command(t_cmds *cmds)
{
	size_t	i;

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
	cmds->exit_code.code = 127;
	cmds->exit_code.last_cmd = cmds->input->cmd_name;
	cmds->cmd_finded->name = NULL;
}

void	read_keyboard(t_cmds *cmds)
{
	ft_printf("> ");
	fgets(cmds->input->data, sizeof(cmds->input->data), stdin);
	cmds->input->data[strcspn(cmds->input->data, "\n")] = 0;
	cmds->input->datacpy = ft_strdup(cmds->input->data);
	cmds->input->cmd_name = ft_strtok(cmds->input->data, " ", 1);
	cmds->input->cmd_args = ft_strtok(NULL, "", 0);
}
