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

#include "../../includes/minishell.h"

void	delete_envs(t_cmds *cmds, char **envs, char *key)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (cmds->envs[i] != NULL)
	{
		printf("key: '%s'\n", key);
		printf("key size: %ld\n", strlen(key));
		printf("check with: %s\n", cmds->envs[i]);
		if (ft_strncmp(cmds->envs[i], key, strlen(key)) == 0)
		{
			write(1, key, strlen(key));
			printf("Removendo %s\n", cmds->envs[i]);
			i++;
		}
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
	char	**args;
	int		result;
	char	*key;

	args = ft_split(cmds->current->full_args, '=');
	key = args[0];
	result = del_env_var(cmds, key);
	free_arr(args);
	return (result);
}
