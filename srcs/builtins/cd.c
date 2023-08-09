/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caalbert <caalbert@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 10:13:53 by caalbert          #+#    #+#             */
/*   Updated: 2023/08/09 01:17:19 by caalbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	cd_adapter(t_cmds *cmds)
{
	char	*path;
	char	*temp;

	if (cmds->current->phrase_parsed != NULL)
	{
		if (cmds->current->phrase_parsed[1] != NULL)
		{
			temp = ft_strdup(cmds->current->phrase_parsed[1]);
		}
		else
			temp = ft_strdup(".");
	}
	path = ft_strdup(temp);
	if (chdir((const char *)path) != 0)
	{
		perror("cd");
		free(temp);
		free(path);
		return (1);
	}
	free(temp);
	free(path);
	return (0);
}
