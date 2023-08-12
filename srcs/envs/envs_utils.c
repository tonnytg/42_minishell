/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envs_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antthoma <antthoma@student.42sp.org.br>    +#+  +:+       +#+        */
/*       calbert  <calbert@student.42sp.org.br>   +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 02:55:02 by antthoma          #+#    #+#             */
/*   Updated: 2023/04/26 00:17:13 by antthoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*getvarenv(t_cmds *cmds, char *var)
{
	char	*found_env;
	char	**temp;
	int		i;

	i = 0;
	temp = NULL;
	if (cmds->envs == NULL)
		return (NULL);
	while (cmds->envs[i] != NULL)
	{
		if (ft_strncmp(cmds->envs[i], var, ft_strlen(var)) == 0)
		{
			temp = ft_split(cmds->envs[i], '=');
			found_env = ft_strdup(temp[1]);
			free_arr(temp);
			return (found_env);
		}
		i++;
	}
	return (NULL);
}
