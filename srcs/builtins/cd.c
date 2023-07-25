/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caalbert <caalbert@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 10:13:53 by caalbert          #+#    #+#             */
/*   Updated: 2023/07/01 22:12:19 by caalbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	cd_adapter(t_cmds *cmds)
{
	const char	*path;
	char		*temp;

	temp = ft_strtrim(cmds->current->full_args, " ");
	path = temp;
	if (chdir(path) != 0)
	{
		perror("cd");
		free(temp);
		return (1);
	}
	free(temp);
	return (0);
}
