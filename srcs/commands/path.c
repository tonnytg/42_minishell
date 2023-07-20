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

char	*get_fullpath(t_cmd_node *current)
{
	char	**paths;
	char	*temp;
	int		i;

	paths = ft_split(getenv("PATH"), ':');
	i = 0;
	while (paths[i])
	{
		temp = ft_strjoin("/", current->cmd_name);
		if (access(ft_strjoin(paths[i], temp), F_OK) == 0)
			return (ft_strjoin(paths[i], temp));
		i++;
	}
	return (NULL);
}
