/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caalbert <caalbert@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 10:14:31 by caalbert          #+#    #+#             */
/*   Updated: 2023/06/13 13:36:19 by caalbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	delete_envs(t_cmds *cmds, char **envs, char *key)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (cmds->envs[i] != NULL)
	{
		if (ft_strncmp(cmds->envs[i], key, ft_strlen(key)) == 0
			&& cmds->envs[i][ft_strlen(key)] == '=')
			i++;
		else
		{
			envs[j] = strdup(cmds->envs[i]);
			i++;
			j++;
		}
	}
	envs[j] = NULL;
}

int	del_env_var(t_cmds *cmds, char *key)
{
	char	**envs;

	if (cmds->envs == NULL)
		return (1);
	envs = ft_calloc(count_arr(cmds->envs), sizeof(char *));
	delete_envs(cmds, envs, key);
	free_arr(cmds->envs);
	cmds->envs = envs;
	return (0);
}

int	unset_adapter(t_cmds *cmds)
{
	int		result;
	char	*key;

	key = cmds->current->phrase_parsed[1];
	result = del_env_var(cmds, key);
	return (result);
}
