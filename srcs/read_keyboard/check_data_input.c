/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_data_input.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caalbert <caalbert@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 02:55:02 by antthoma          #+#    #+#             */
/*   Updated: 2023/07/02 12:43:45 by caalbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_empty_data(t_cmds *cmds)
{
	int	i;

	i = 0;
	while (cmds->input->data[i] != '\0'
		&& cmds->input->data[i] != '\n')
	{
		if (cmds->input->data[i] != ' '
			&& cmds->input->data[i] != '\t')
		{
			return (0);
		}
		i++;
	}
	return (1);
}

char	*check_data_input(t_cmds *cmds)
{
	if (is_empty_data(cmds))
		return (NULL);
	return (cmds->input->data);
}
