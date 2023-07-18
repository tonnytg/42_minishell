/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c 				                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antthoma <antthoma@student.42sp.org.br>    +#+  +:+       +#+        */
/*       calbert  <calbert@student.42sp.org.br>   +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 02:55:02 by antthoma          #+#    #+#             */
/*   Updated: 2023/06/18 00:17:13 by antthoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*check_path(t_cmd_node *node)
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
		name = ft_strjoin("/", node->cmd_name);
		path_complete = ft_strjoin(path[i], name);
		return_access = access(path_complete, F_OK);
		if (return_access == 0)
			return (path_complete);
		i++;
	}
	return (NULL);
}
