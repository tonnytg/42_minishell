/* ************************************************************************** */
/*	                                                                        */
/*                                                        :::      ::::::::   */
/*   directory_handler.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caalbert <caalbert@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 00:44:18 by caalbert          #+#    #+#             */
/*   Updated: 2023/08/11 00:45:53 by caalbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*parse_special_folders(t_cmds *cmds, char *str)
{
	char	*dir;
	char	*result;

	if (ft_strcmp(str, "..") == 0)
		return (ft_strdup(".."));
	if (ft_strcmp(str, "-") == 0)
	{
		if (cmds->previous_dir)
			return (ft_strdup(cmds->previous_dir));
		else
			return (NULL);
	}
	if (str[0] == '~')
	{
		dir = get_env_value(cmds, "HOME");
		if (dir == NULL)
			return (NULL);
		if (str[1] == '/')
			result = ft_strjoin(dir, str + 1);
		else
			result = ft_strdup(dir);
		return (result);
	}
	return (NULL);
}

static char	*parse_relative_folder(char *str)
{
	char	*dir;
	char	*result;

	if (ft_strncmp(str, "./", 2) == 0)
	{
		dir = getcwd(NULL, 0);
		result = ft_strjoin(dir, str + 1);
		free(dir);
		return (result);
	}
	return (ft_strdup(str));
}

char	*parse_to_folder(t_cmds *cmds, char *str)
{
	char	*result;

	result = parse_special_folders(cmds, str);
	if (result)
		return (result);
	return (parse_relative_folder(str));
}
