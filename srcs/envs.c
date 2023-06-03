/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antthoma <antthoma@student.42sp.org.br>    +#+  +:+       +#+        */
/*       calbert  <calbert@student.42sp.org.br>   +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 02:55:02 by antthoma          #+#    #+#             */
/*   Updated: 2023/04/26 00:17:13 by antthoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_envs(t_cmds *cmds)
{
	int	i;

	i = 0;
	while (cmds->envs[i] != NULL)
	{
		free(cmds->envs[i]);
		i++;
	}
	free(cmds->envs);
}

int	count_envp(char **envp)
{
	int	i;

	i = 0;
	while (envp[i] != NULL)
		i++;
	return (i);
}

void	set_envs(char **envp, t_cmds *cmds)
{
	int	i;

	i = 0;
	while (envp[i] != NULL)
	{
		cmds->envs[i] = ft_strdup(envp[i]);
		i++;
	}
	cmds->envs[i] = NULL;
}

int	append_envs(t_cmds *cmds, char *name, char *value)
{
	int		i;
	char	*env;
	char	*name_equal;

	i = 0;
	while (cmds->envs[i] != NULL)
		i++;
	name_equal = ft_strjoin(name, "=");
	env = ft_strjoin(name_equal, value);
	cmds->envs[i] = env;
	free(name_equal);
	cmds->envs[i + 1] = NULL;
	return (0);
}
