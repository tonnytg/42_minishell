/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caalbert <caalbert@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 10:13:53 by caalbert          #+#    #+#             */
/*   Updated: 2023/08/11 12:36:23 by caalbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*get_correct_path(t_cmds *cmds, char *input_path)
{
	char	*result_path;
	char	*home;

	if (strcmp(input_path, "~") == 0)
	{
		home = getenv("HOME");
		if (home != NULL)
			result_path = ft_strdup(home);
		else
			return (NULL);
	}
	else if (strcmp(input_path, "-") == 0)
	{
		if (cmds->previous_dir == NULL)
			return (NULL);
		else
			result_path = ft_strdup(cmds->previous_dir);
	}
	else
		result_path = ft_strdup(input_path);
	return (result_path);
}

int	change_directory(t_cmds *cmds, char *path, char *temp)
{
	if (!path)
	{
		free(temp);
		return (1);
	}
	if (cmds->previous_dir != NULL)
		free(cmds->previous_dir);
	cmds->previous_dir = getcwd(NULL, 0);
	if (chdir((const char *)path) != 0)
	{
		free(temp);
		free(path);
		return (1);
	}
	free(temp);
	free(path);
	return (0);
}

int	cd_adapter(t_cmds *cmds)
{
	char	*temp;
	char	*path;

	if (cmds->current->phrase_parsed != NULL)
	{
		if (cmds->current->phrase_parsed[1] != NULL)
			temp = ft_strdup(cmds->current->phrase_parsed[1]);
		else
			temp = ft_strdup(".");
	}
	path = get_correct_path(cmds, temp);
	return (change_directory(cmds, path, temp));
}
