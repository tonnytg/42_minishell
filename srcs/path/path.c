/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caalbert <caalbert@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 02:55:02 by antthoma          #+#    #+#             */
/*   Updated: 2023/06/06 10:21:31 by caalbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*build_complete_path(t_cmds *cmds, char *path, char *cmd_name)
{
	char	*path_complete;
	char	*tmp;

	if (cmds->current->cmd_name != NULL && cmds->current->cmd_name[0] == '/')
		return (ft_strdup(cmds->current->cmd_name));
	tmp = ft_strjoin(path, "/");
	path_complete = ft_strjoin(tmp, cmd_name);
	free(tmp);
	return (path_complete);
}

int	check_access(char *path_complete)
{
	if (access(path_complete, F_OK) == 0)
	{
		if (access(path_complete, X_OK) == 0)
			return (1);
		else
			return (0);
	}
	return (0);
}

char	*get_fullpath(t_cmds *cmds)
{
	char	**path;
	char	*result;
	int		return_access;
	int		i;

	result = getvarenv(cmds, "PATH");
	path = ft_split(result, ':');
	i = 0;
	free(result);
	while (path != NULL && path[i])
	{
		result = build_complete_path(cmds, path[i],
				cmds->current->cmd_name);
		return_access = check_access(result);
		if (return_access)
		{
			free_split(path);
			return (result);
		}
		free(result);
		i++;
	}
	free_split(path);
	return (NULL);
}
