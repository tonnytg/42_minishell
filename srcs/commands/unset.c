/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caalbert <caalbert@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 10:14:31 by caalbert          #+#    #+#             */
/*   Updated: 2023/06/12 23:16:15 by caalbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern char	**environ;

// int	ft_unsetenv(const char *name)
// {
// 	int	i;
// 	int	len;

// 	i = 0;
// 	len = ft_strlen(name);
// 	while (environ[i])
// 	{
// 		if (ft_strncmp(environ[i], name, len) == 0 && environ[i][len] == '=')
// 		{
// 			while (environ[i])
// 			{
// 				environ[i] = environ[i + 1];
// 				i++;
// 			}
// 			return (0);
// 		}
// 		i++;
// 	}
// 	return (-1);
// }

int	unset_adapter(t_cmds *cmds)
{
	(void) cmds;
	printf("⚠️ Need to create!!! ⚠️\n");
	return (0);
	
	/*
	if (getenv(cmds->input->cmd_args) != NULL)
	{
		unsetenv(cmds->input->cmd_args);
		if (getenv(cmds->input->cmd_args) == NULL)
			return (0);
		else
			return (1);
	}
	else
		return (1);
	*/
}
