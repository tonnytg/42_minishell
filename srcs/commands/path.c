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

void free_split(char **split_array)
{
	if (split_array == NULL)
		return;

	// Iterar sobre o array de strings
	for (int i = 0; split_array[i] != NULL; i++)
	{
		free(split_array[i]); // Liberar a memória de cada string
	}

	free(split_array); // Liberar a memória do array de strings
}

char	*get_fullpath(t_cmd_node *current)
{
	char	**path;
	int		i;
	char	*path_complete;
	int		return_access;
	char	*name;

	path = ft_split(getenv("PATH"), ':');
	i = 0;
	while (path[i])
	{
		name = ft_strjoin("/", current->cmd_name);
		path_complete = ft_strjoin(path[i], name);
		free(name);
		return_access = access(path_complete, F_OK);
		if (return_access == 0)
		{
			free_split(path);
			return (path_complete);
		}
		i++;
	}
	free_split(path);
	return (NULL);
}
