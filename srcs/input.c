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

t_command	*find_command(t_cmds *cmds, const char *name)
{
	int	i;

	i = 0;
	while (i < cmds->num_cmds && name != NULL)
	{
		if (ft_strcmp(cmds->cmd[i].name, name) == 0)
		{
			return (&cmds->cmd[i]);
		}
		i++;
	}
	return (NULL);
}

void	read_keyboard(t_input *data)
{
	ft_printf("> ");
	fgets(data->input, sizeof(data->input), stdin);
	data->input[strcspn(data->input, "\n")] = 0;
	data->cmd_name = strtok(data->input, " ");
	data->cmd_arg = strtok(NULL, "");
}
