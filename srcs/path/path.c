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

char	*getvarenv(t_cmds *cmds, char *var)
{
	char	*found_env;
	int		i;

	i = 0;
	if (cmds->envs == NULL)
		return (NULL);
	while (cmds->envs[i] != NULL)
	{
		if (ft_strncmp(cmds->envs[i], var, ft_strlen(var)) == 0)
		{
			found_env = ft_strdup(cmds->envs[i]);
			return (found_env);
		}
		i++;
	}
	return (NULL);
}

void	free_split(char **split_array)
{
	int	i;

	i = 0;
	if (split_array == NULL)
		return ;
	while (split_array[i] != NULL)
	{
		free(split_array[i]);
		i++;
	}
	free(split_array);
}

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
	int		i;
	char	*path_complete;
	int		return_access;
	char	*value_path;

	// TODO: pegar o cmds->envs
	i = 0;
	if (cmds->envs == NULL)
		return (NULL);
	value_path = NULL;
	while (cmds->envs[i])
	{
		if (ft_strncmp(cmds->envs[i], "PATH=", 5) == 0)
			value_path = ft_strdup(cmds->envs[i] + 5);
		i++;
	}
	path = ft_split(value_path, ':');
	if (path == NULL)
		return (NULL);
	i = 0;
	while (path[i])
	{
		printf("[get_fullpath] path: '%s'\n", path[i]);
		path_complete = build_complete_path(cmds, path[i],
				cmds->current->cmd_name);
		return_access = check_access(path_complete);
		printf("[get_fullpath] path_complete: '%s'\n", path_complete);
		printf("[get_fullpath] return_access: '%d'\n", return_access);
		if (return_access)
		{
			free_split(path);
			return (path_complete);
		}
		free(path_complete);
		i++;
	}
	free_split(path);
	return (NULL);
}
